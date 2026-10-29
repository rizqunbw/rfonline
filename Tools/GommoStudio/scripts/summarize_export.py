"""Validate the decompiler export and publish selected RF functions with symbol annotations."""
import gzip
import hashlib
import json
from pathlib import Path
import re

ROOT=Path(__file__).resolve().parents[1]/'analysis'
SELECTED=(
    'gommo/pkg/assets/rfpack.ReadRFSEntries','gommo/pkg/assets/rfpack.EncodeRFS',
    'gommo/pkg/assets/rfpack.NewRFS','gommo/pkg/assets/rfpack.NewRPK',
    'gommo/pkg/assets/r3char.LoadModel','gommo/pkg/assets/r3char.LoadSkeleton',
    'gommo/pkg/assets/r3char.LoadClip','gommo/pkg/assets/r3char.EncodeModel',
    'gommo/pkg/assets/r3.LoadBSP','gommo/pkg/assets/r3.LoadEBP',
    'gommo/pkg/assets/rfdata.Decode','gommo/pkg/assets/ifcfg.Parse',
)


def main():
    from read_editor import functions
    def zipped(name):
        with gzip.open(ROOT/name,'rt') as f:return json.load(f)
    symbols=zipped('go-functions.json.gz');lookup={r['address'][2:].lower():r['name'] for r in symbols}
    index=zipped('decompilation-index.json.gz');by_address={r['address']:r for r in index}
    source=zipped('application-functions.json.gz')
    if [r['address'] for r in index]!=[r['address'] for r in source]:raise ValueError('Export index does not match source symbol order')
    seen=[];selected=[]
    for address,name,code in functions():
        seen.append(address)
        if name not in SELECTED:continue
        row=by_address[address]
        if not row['decompiled']:continue
        callees=sorted(set(re.findall(r'FUN_([0-9a-fA-F]+)',code)))
        notes=['/* Generated pseudocode, NOT original Go source.',f' * Go symbol: {name}',f' * VA: {address}',
               ' * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.',
               ' * Calls recognized from retained Go metadata:']
        for target in callees:
            if target.lower() in lookup:notes.append(f' * FUN_{target}: {lookup[target.lower()]}'.replace('*/','* /'))
        notes+=[' */','']
        filename=address[2:]+'_'+name.rsplit('.',1)[-1]+'.c'
        path=ROOT/'selected'/filename
        path.parent.mkdir(exist_ok=True)
        path.write_text('\n'.join(notes)+'\n'.join(line.rstrip() for line in code.splitlines()).strip()+'\n')
        selected.append(dict(name=name,address=address,file='selected/'+filename))
    if seen!=[r['address'] for r in index]:raise ValueError('Pseudocode archive/index mismatch')
    core=json.loads((ROOT/'rf-format-functions.json').read_text())
    failures=[r for r in index if not r['decompiled']]
    log=(ROOT/'analysis.log').read_text()
    timeout=re.search(r'Analysis timed out at (\d+) seconds',log)
    added=re.search(r'additionalEntriesFromPclntab=(\d+)',log)
    type_error=re.search(r'Caused by: java.io.EOFException: Invalid index: \d+',log)
    report=dict(binary_sha256=json.loads((ROOT/'metadata.json').read_text())['sha256'],
                auto_analysis_complete='Analysis succeeded for file:' in log and not timeout,
                auto_analysis_timeout_seconds=int(timeout[1]) if timeout else None,
                go_type_recovery_error=type_error[0] if type_error else None,
                functions_added_from_pclntab=int(added[1]) if added else None,
                requested=len(index),decompiled=len(index)-len(failures),failed=len(failures),
                core_requested=len(core),core_decompiled=sum(by_address[r['address']]['decompiled'] for r in core),
                selected=selected,failed_functions=failures,
                archive_sha256=hashlib.sha256((ROOT/'application-decompiled.c.gz').read_bytes()).hexdigest(),
                caveat='Pseudocode completion is not proof of correct types, source recovery, feature functionality or full binary coverage.')
    (ROOT/'coverage.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({k:report[k] for k in ('requested','decompiled','failed','core_requested','core_decompiled')}))


if __name__=='__main__':main()
