"""Read verified payloads by the resource IDs from Player.xlsx."""
import hashlib
import json
from pathlib import Path
from extract_rfs import entries

ROOT = Path(__file__).resolve().parents[1]


class PlayerResources:
    def __init__(self, root=ROOT):
        self.root = root
        self.data = json.loads((root / 'resources.json').read_text())
        digest = hashlib.sha256((root / 'Player.xlsx').read_bytes()).hexdigest()
        if digest != self.data['workbook']['sha256']:
            raise ValueError('Player.xlsx changed; run catalog_player.py before building')
        self.bones = {b['resourceId']: b for b in self.data['bones']}
        self.meshes = {m['resourceId']: m for m in self.data['meshes']}
        self._archives = {}

    def mesh(self, resource_id):
        record = self.meshes[resource_id.upper()]
        if record['status'] != 'available' or not record['boneAvailable']:
            raise ValueError(f'Mesh resource is not ready: {resource_id}')
        reference = record['candidates'][0]
        archive = reference['archive']
        if archive not in self._archives:
            raw = (self.root / archive).read_bytes()
            self._archives[archive] = raw, {e['name']: e for e in entries(raw)}
        raw, table = self._archives[archive]
        actual = table.get(reference['name'])
        if actual is None or any(actual[k] != reference[k] for k in ['offset', 'size', 'sha256']):
            raise ValueError(f'Stale or changed mesh archive: {archive}')
        bone_ref = self.bones[record['boneResourceId']]['files']['FileName']
        bone_path = self.root / bone_ref['path']
        if hashlib.sha256(bone_path.read_bytes()).hexdigest() != bone_ref['sha256']:
            raise ValueError('Skeleton changed; regenerate resource catalog')
        return dict(record=record, archive=self.root / archive, bone=bone_path,
                    payload=raw[actual['offset']:actual['offset']+actual['size']])
