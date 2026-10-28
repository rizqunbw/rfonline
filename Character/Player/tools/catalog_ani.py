"""Index uploaded animation archives, validate clips, and compare loose copies."""
from pathlib import Path
import hashlib
import json
import zipfile
from extract_rfs import entries
from inspect_ani import inspect

ROOT=Path(__file__).resolve().parents[1]/'Ani'


def catalog(root=ROOT):
    archives=[];failures=[];by_name={};clips=0
    for path in sorted(root.glob('*.RFS')):
        data=path.read_bytes();files=entries(data);records=[];bone_names=set()
        for entry in files:
            payload=data[entry['offset']:entry['offset']+entry['size']]
            item=dict(entry)
            try:
                if Path(entry['name']).suffix.lower()!='.ani':raise ValueError('Entry is not ANI')
                info=inspect(payload);bone_names.update(o['name'] for o in info['objects'])
                item['animation']={k:v for k,v in info.items() if k!='objects'}
                item['nonmonotonicTracks']=sum(not t['nondecreasing'] for o in info['objects'] for t in o['tracks'].values())
            except (ValueError,UnicodeError) as error:
                item['error']=str(error);failures.append({'archive':path.name,'entry':entry['name'],'error':str(error)})
            by_name.setdefault(entry['name'].casefold(),[]).append({'archive':path.name,'sha256':entry['sha256']})
            records.append(item);clips+=1
        archives.append({'name':path.name,'files':records,'objectNames':sorted(bone_names)})
    loose=[]
    for path in sorted(root.glob('*.ANI')):
        data=path.read_bytes();sha=hashlib.sha256(data).hexdigest();info=inspect(data)
        loose.append({'name':path.name,'sha256':sha,'animation':info,
                      'archiveCopies':[{**record,'identical':record['sha256']==sha} for record in by_name.get(path.name.casefold(),[])]})
    temporary=[]
    for path in sorted(root.glob('*.tmp')):
        item={'name':path.name,'isZip':zipfile.is_zipfile(path),'members':[]}
        if item['isZip']:
            with zipfile.ZipFile(path) as archive:
                for member in archive.infolist():
                    if member.is_dir():continue
                    if member.file_size>32*1024*1024:raise ValueError('Unexpected large TMP member')
                    data=archive.read(member);name=Path(member.filename).name;target=root/name
                    item['members'].append({'name':member.filename,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest(),
                                            'identicalToLooseFile':target.is_file() and target.read_bytes()==data})
        temporary.append(item)
    listed=(root/'RFSInfo.dat').read_text(encoding='ascii').splitlines()
    available={p.name.casefold():p.name for p in root.glob('*.RFS')}
    return {'archiveCount':len(archives),'clipCount':clips,'uniqueClipNames':len(by_name),
            'archives':archives,'looseAnimations':loose,'temporaryFiles':temporary,
            'registry':{'listed':listed,'missing':[n for n in listed if n.casefold() not in available],
                        'unlisted':[n for lower,n in available.items() if lower not in {s.casefold() for s in listed}]},
            'parseFailures':failures}


if __name__=='__main__':
    result=catalog();(ROOT/'catalog.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({k:result[k] for k in ('archiveCount','clipCount','uniqueClipNames','registry','parseFailures')},indent=2))
