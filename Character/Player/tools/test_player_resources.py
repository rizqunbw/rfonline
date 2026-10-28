"""Verify workbook resolution, uploaded mesh preservation and missing assets."""
import hashlib
import json
from pathlib import Path
import unittest
from catalog_player import ROOT, catalog, read_tables
from player_resources import PlayerResources


class ResourceTests(unittest.TestCase):
    def test_uploads_preserved_and_no_case_collisions(self):
        records = json.loads((ROOT/'Mesh/uploads-00.json').read_text())
        self.assertEqual(len(records), 16)
        for record in records:
            data = (ROOT/record['path']).read_bytes()
            self.assertEqual(len(data), record['bytes'])
            self.assertEqual(hashlib.sha256(data).hexdigest(), record['sha256'])
        names = [p.name.casefold() for p in (ROOT/'Mesh').iterdir()]
        self.assertEqual(len(names), len(set(names)))
        self.assertEqual(next(r['path'] for r in records if r['uploadedName']=='BFF00.RFS'), 'Mesh/BFF00.rfs')

    def test_catalog_matches_sources_and_workbook(self):
        resources, meshes = catalog()
        self.assertEqual(resources, json.loads((ROOT/'resources.json').read_text()))
        self.assertEqual(meshes, json.loads((ROOT/'Mesh/catalog.json').read_text()))
        self.assertEqual(resources['summary']['workbookRows'], {'Bone':5, 'Mesh':6808, 'Ani':2056})
        self.assertEqual(resources['summary']['uploadedMeshesWithWorkbookId'], 354)
        self.assertEqual(resources['summary']['uploadedMeshesWithAllTextures'], 213)
        bone_ids = {b['resourceId'] for b in resources['bones']}
        self.assertTrue(all(m['boneResourceId'] in bone_ids for m in resources['meshes']))

    def test_case_insensitive_id_and_verified_payload(self):
        registry = PlayerResources()
        resource = registry.mesh('001002ab')
        self.assertEqual(resource['record']['boneResourceId'], '00000001')
        self.assertEqual(resource['bone'].name, 'BelFemale.bn')
        self.assertEqual(resource['payload'], (ROOT/'Mesh/BFF00/BELFEMALE_ARMOR_UPPER_171.msh').read_bytes())
        model = json.loads((ROOT.parents[1]/'Map/Platform01/assets/character/bellato-171.json').read_text())
        for resource_id in model['meshResourceIds']:
            self.assertEqual(registry.mesh(resource_id)['record']['boneResourceId'], model['boneResourceId'])

    def test_missing_default_face_is_explicit(self):
        registry = PlayerResources()
        face = next(r for r in registry.data['meshes'] if r['fields']['FileName']=='BELFEMALE_DEFAULT_FACE_000.MSH')
        self.assertEqual(face['status'], 'missing')
        self.assertEqual(face['candidates'], [])
        with self.assertRaises(ValueError): registry.mesh(face['resourceId'])
        with self.assertRaises(KeyError): registry.mesh('FFFFFFFF')


if __name__ == '__main__': unittest.main()
