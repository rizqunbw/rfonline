"""Source integrity and bind/skin checks for the rendered character."""
import hashlib
import io
import json
from pathlib import Path
import unittest
import numpy as np
from PIL import Image
from build_character import ROOT, OUT, C, KEY, read_bones, read_mesh
from extract_rfs import entries
from inspect_ani import inspect as inspect_animation


class CharacterTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.model = json.loads((OUT / 'bellato-171.json').read_text())
        cls.bones = read_bones((ROOT / 'Bone/BelFemale.bn').read_bytes())

    def test_uploaded_texture_archives_and_rendered_source_hashes(self):
        manifest = json.loads((ROOT / 'Tex/manifest.json').read_text())
        self.assertEqual(len(manifest), 28)
        self.assertEqual({p.name for p in (ROOT/'Tex').glob('*.RFS')}, {r['name'] for r in manifest})
        for record in manifest:
            raw = (ROOT / 'Tex' / record['name']).read_bytes()
            self.assertEqual(len(raw), record['bytes'])
            self.assertEqual(hashlib.sha256(raw).hexdigest(), record['sha256'])
            self.assertEqual(entries(raw), record['entries'])
            # Every uploaded RFT payload decodes as DDS, including unused races.
            for entry in record['entries']:
                data = raw[entry['offset']:entry['offset']+entry['size']]
                if data[:4] != b'DDS ': data = bytes(a ^ b for a, b in zip(data[:128], KEY)) + data[128:]
                Image.open(io.BytesIO(data)).load()
        for record in self.model['sources']:
            self.assertEqual(hashlib.sha256((ROOT/record['path']).read_bytes()).hexdigest(), record['sha256'])

    def test_bind_pose_and_mesh_data(self):
        names = {b['name']: i for i, b in enumerate(self.bones)}
        self.assertEqual(len(names), 25)
        expected = []
        for slot in ['GLOVES', 'HELMET', 'LOWER', 'SHOES', 'UPPER']:
            expected.extend(read_mesh((ROOT/f'Mesh/BFF00/BELFEMALE_ARMOR_{slot}_171.msh').read_bytes(), names))
        raw = (ROOT/'Mesh/DEFAULTBF.RFS').read_bytes()
        for name in ['BELFEMALE_DEFAULT_FACE_000.msh', 'BELFEMALE_DEFAULT_HELMET_000.msh']:
            entry = next(e for e in entries(raw) if e['name']==name)
            expected.extend(read_mesh(raw[entry['offset']:entry['offset']+entry['size']], names))
        self.assertEqual(expected, [{k:v for k,v in m.items() if k not in ['slot','resourceId']} for m in self.model['meshes']])
        self.assertEqual(sum(len(m['positions'])//9 for m in expected), 4056)
        self.assertEqual({m['slot'] for m in self.model['meshes']}, {'gloves','helmet','lower','shoes','upper','face','hair'})
        skin = []
        for bone, exported in zip(self.bones, self.model['bones']):
            inverse = np.array(exported['inverseBind']).reshape(4, 4).T
            skin.append(C @ bone['world'] @ C.T @ inverse)
        for mesh in expected:
            positions = np.array(mesh['positions']).reshape(-1, 3)
            weights = np.array(mesh['weights']).reshape(-1, 4)
            joints = np.array(mesh['joints']).reshape(-1, 4)
            self.assertTrue(np.allclose(weights.sum(axis=1), 1))
            posed = np.zeros_like(positions)
            p = np.column_stack([positions, np.ones(len(positions))])
            for k in range(4):
                matrices = np.array(skin)[joints[:, k]]
                posed += np.einsum('nij,nj->ni', matrices, p)[:, :3] * weights[:, k, None]
            self.assertTrue(np.allclose(posed, positions, atol=1e-5))

    def test_decoded_textures_are_lossless(self):
        self.assertEqual(len(self.model['textures']), 7)
        for texture in self.model['textures']:
            raw = (ROOT/texture['archive']).read_bytes()
            e = next(e for e in entries(raw) if e['name']==texture['original'])
            data = raw[e['offset']:e['offset']+e['size']]
            data = bytes(a ^ b for a, b in zip(data[:128], KEY)) + data[128:]
            expected = Image.open(io.BytesIO(data)).convert('RGBA')
            actual = Image.open(OUT / texture['file']).convert('RGBA')
            self.assertEqual(expected.size, actual.size)
            self.assertEqual(expected.tobytes(), actual.tobytes())

    def test_animation_tracks_come_from_original_keys(self):
        for clip in self.model['clips']:
            raw = (ROOT / 'Ani' / clip['archive']).read_bytes()
            entry = next(e for e in entries(raw) if e['name'] == clip['source'])
            source = inspect_animation(raw[entry['offset']:entry['offset']+entry['size']], True)
            objects = {o['name']: o for o in source['objects']}
            for track in clip['tracks']:
                name = self.bones[track['bone']]['name']
                original = objects[name]['tracks'][track['channel']]['values']
                self.assertEqual(track['times'], [tick/4800 for tick in dict.fromkeys(k['tick'] for k in original)])
                self.assertTrue(np.isfinite(track['values']).all())
            self.assertGreater(len(clip['tracks']), 20)

    def test_invalid_skeleton_rejected(self):
        raw = (ROOT / 'Bone/BelFemale.bn').read_bytes()
        for bad in [b'\xff\xff', raw[:-1], raw+b'padding']:
            with self.assertRaises(ValueError): read_bones(bad)


if __name__ == '__main__': unittest.main()
