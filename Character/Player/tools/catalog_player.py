"""Resolve Player.xlsx resource IDs to uploaded assets without executing cells.

Requires openpyxl. Windows resource names are matched case-insensitively, but
actual repository paths and original bytes are preserved. Missing references
and differing same-name payloads remain explicit instead of being guessed.
"""
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import openpyxl
from extract_rfs import entries
from inspect_msh import inspect

ROOT = Path(__file__).resolve().parents[1]


def read_tables(path):
    workbook = openpyxl.load_workbook(path, read_only=True, data_only=False, keep_links=False)
    tables = {}
    try:
        for sheet_name in ['Bone', 'Mesh', 'Ani']:
            sheet = workbook[sheet_name]
            rows = iter(sheet.iter_rows())
            next(rows)  # RF field types, preserved in the original workbook.
            headers = [c.value for c in next(rows)]
            records, ids = [], set()
            for row in rows:
                if row[0].value is None:
                    continue
                if any(c.data_type == 'f' for c in row):
                    raise ValueError(f'Formula cells are not resource data: {sheet_name}/{row[0].row}')
                fields = {h: c.value for h, c in zip(headers, row) if h and h != 'END'}
                resource_id = str(fields['ID']).upper()
                if len(resource_id) != 8 or any(c not in '0123456789ABCDEF' for c in resource_id) or resource_id in ids:
                    raise ValueError(f'Invalid/duplicate resource ID: {sheet_name}/{resource_id}')
                ids.add(resource_id)
                records.append(dict(resourceId=resource_id, row=row[0].row, fields=fields))
            tables[sheet_name] = records
    finally:
        workbook.close()
    return tables


def references(directory, root=ROOT):
    index = defaultdict(list)
    for archive in sorted(directory.iterdir()):
        if archive.suffix.lower() != '.rfs':
            continue
        data = archive.read_bytes()
        for entry in entries(data):
            index[entry['name'].casefold()].append(dict(archive=str(archive.relative_to(root)), **entry))
    return index


def resolve(record, index, folder):
    parts = [p.casefold() for p in record['fields']['PathName'].replace('\\', '/').split('/') if p not in ['', '.']]
    candidates = index.get(record['fields']['FileName'].casefold(), []) if parts == ['character', 'player', folder.lower()] else []
    status = 'missing' if not candidates else 'available' if len({c['sha256'] for c in candidates}) == 1 else 'ambiguous'
    return dict(**record, status=status, candidates=candidates)


def catalog(root=ROOT):
    # All archive payload bounds and digests are re-read, never trusted from a previous catalog.
    tables = read_tables(root / 'Player.xlsx')
    mesh_index, ani_index, tex_index = [references(root / d, root) for d in ['Mesh', 'Ani', 'Tex']]
    bone_files = {p.name.casefold(): p for p in (root / 'Bone').iterdir() if p.is_file()}
    bones = []
    for record in tables['Bone']:
        refs = {}
        for key in ['FileName', 'BBoxName']:
            path = bone_files.get(str(record['fields'][key]).casefold())
            refs[key] = None if path is None else dict(path=str(path.relative_to(root)), sha256=hashlib.sha256(path.read_bytes()).hexdigest())
        bones.append(dict(**record, status='available' if all(refs.values()) else 'missing', files=refs))
    bone_ids = {b['resourceId']: b for b in bones}
    meshes = []
    for record in tables['Mesh']:
        resolved = resolve(record, mesh_index, 'Mesh')
        resolved['boneResourceId'] = str(record['fields']['BoneID']).upper()
        resolved['boneAvailable'] = bone_ids.get(resolved['boneResourceId'], {}).get('status') == 'available'
        meshes.append(resolved)
    animations = [resolve(record, ani_index, 'Ani') for record in tables['Ani']]
    tex_by_stem = defaultdict(list)
    for refs in tex_index.values():
        for ref in refs:
            tex_by_stem[Path(ref['name']).stem.casefold()].append(ref)
    resource_ids = defaultdict(list)
    for mesh in meshes:
        if mesh['status'] != 'missing':
            resource_ids[mesh['fields']['FileName'].casefold()].append(mesh['resourceId'])
    archive_data = {}
    parsed_meshes, ancillary = [], []
    for key, refs in sorted(mesh_index.items()):
        for ref in refs:
            if ref['archive'] not in archive_data:
                archive_data[ref['archive']] = (root / ref['archive']).read_bytes()
            raw = archive_data[ref['archive']]
            payload = raw[ref['offset']:ref['offset']+ref['size']]
            if Path(ref['name']).suffix.lower() != '.msh':
                ancillary.append(ref)
                continue
            try:
                result = inspect(payload)
                inspection = dict(status='parsed')
            except ValueError as error:
                result = None
                inspection = dict(status='unsupported' if payload.startswith(b'MESH08') else 'inspection_failed', reason=str(error))
            textures = []
            for name in sorted({o['texture'] for o in result['objects'] if o['texture']} if result else []):
                candidates = tex_by_stem.get(Path(name).stem.casefold(), [])
                textures.append(dict(name=name, status='missing' if not candidates else 'available' if len({c['sha256'] for c in candidates}) == 1 else 'ambiguous', candidates=candidates))
            parsed_meshes.append(dict(**ref, resourceIds=resource_ids.get(key, []), inspection=inspection, mesh=result, textures=textures))
    summary = dict(workbookRows={k: len(v) for k, v in tables.items()},
                   boneStatus=dict(Counter(r['status'] for r in bones)),
                   meshStatus=dict(Counter(r['status'] for r in meshes)),
                   animationStatus=dict(Counter(r['status'] for r in animations)),
                   uploadedMeshArchives=len(archive_data), uploadedMeshes=len(parsed_meshes),
                   uploadedMeshesWithWorkbookId=sum(bool(m['resourceIds']) for m in parsed_meshes),
                   inspectionStatus=dict(Counter(m['inspection']['status'] for m in parsed_meshes)),
                   uploadedMeshesWithAllTextures=sum(m['mesh'] is not None and bool(m['textures']) and all(t['status']=='available' for t in m['textures']) for m in parsed_meshes),
                   ancillaryMeshFolderPayloads=ancillary,
                   missingTextureNames=sorted({t['name'] for m in parsed_meshes for t in m['textures'] if t['status']=='missing'}))
    registries = {}
    for folder in ['Mesh', 'Tex']:
        registry_path = root/folder/'RFSInfo.dat'
        if registry_path.exists():
            listed = [line.strip() for line in registry_path.read_text(encoding='ascii').splitlines() if line.strip()]
            available = {p.name.casefold(): p.name for p in (root/folder).iterdir() if p.suffix.lower()=='.rfs'}
            listed_lower = {n.casefold() for n in listed}
            registries[folder] = dict(listed=len(listed), availableListed=sum(n.casefold() in available for n in listed),
                missing=[n for n in listed if n.casefold() not in available],
                unlisted=[n for key, n in sorted(available.items()) if key not in listed_lower])
    summary['archiveRegistries'] = registries
    resources = dict(workbook=dict(path='Player.xlsx', sha256=hashlib.sha256((root/'Player.xlsx').read_bytes()).hexdigest()),
                     summary=summary, bones=bones, meshes=meshes, animations=animations)
    return resources, parsed_meshes


def main():
    resources, meshes = catalog()
    (ROOT / 'resources.json').write_text(json.dumps(resources, separators=(',', ':'), allow_nan=False)+'\n')
    (ROOT / 'Mesh/catalog.json').write_text(json.dumps(meshes, separators=(',', ':'), allow_nan=False)+'\n')
    (ROOT / 'resource-summary.json').write_text(json.dumps(resources['summary'], indent=2)+'\n')
    print(json.dumps({k: v for k, v in resources['summary'].items() if k != 'missingTextureNames'}, indent=2))


if __name__ == '__main__': main()
