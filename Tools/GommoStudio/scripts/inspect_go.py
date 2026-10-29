"""Read Go build info and Go 1.20+ pclntab metadata in a PE64 file, without execution."""
import argparse
from collections import Counter
import gzip
import hashlib
import json
from pathlib import Path
import re
import struct

CORE = ('gommo/pkg/assets/rfpack.', 'gommo/pkg/assets/r3.', 'gommo/pkg/assets/r3char.',
        'gommo/pkg/assets/rfdata.', 'gommo/pkg/assets/bsp.', 'gommo/pkg/assets/r3compile.',
        'gommo/pkg/assets/rfplacement.', 'gommo/pkg/assets/rfmapdata.', 'gommo/pkg/assets/dsui.',
        'gommo/pkg/assets/ifcfg.', 'gommo/pkg/assets/rml.', 'gommo/pkg/assets/r3light.',
        'gommo/games/rfclient.')


class Reader:
    def __init__(self, data): self.data=data
    def take(self, at, count):
        if at<0 or count<0 or at+count>len(self.data): raise ValueError('Truncated or invalid range')
        return self.data[at:at+count]
    def unpack(self, fmt, at): return struct.unpack(fmt,self.take(at,struct.calcsize(fmt)))
    def string(self, at, limit):
        if at<0 or limit<0 or at>=len(self.data):raise ValueError('Invalid metadata string range')
        end=self.data.find(b'\0',at,min(at+limit,len(self.data)))
        if end<0:raise ValueError('Unterminated metadata string')
        return self.data[at:end].decode('utf-8','replace')
    def uvarint(self, at):
        value=0
        for i in range(10):
            byte=self.take(at+i,1)[0]
            if i==9 and byte>1:raise ValueError('Varint overflow')
            value|=(byte&127)<<(i*7)
            if byte<128:return value,at+i+1
        raise ValueError('Invalid varint')
    def gostring(self, at):
        size,at=self.uvarint(at)
        return self.take(at,size),at+size


def inspect(data):
    r=Reader(data)
    if r.take(0,2)!=b'MZ':raise ValueError('Not a PE file')
    pe=r.unpack('<I',0x3c)[0]
    if r.take(pe,4)!=b'PE\0\0':raise ValueError('Invalid PE signature')
    machine,count=r.unpack('<HH',pe+4);optional_size=r.unpack('<H',pe+20)[0]
    if machine!=0x8664 or r.unpack('<H',pe+24)[0]!=0x20b:raise ValueError('Expected x86-64 PE32+')
    if not 1<=count<=96:raise ValueError('Invalid section count')
    imagebase=r.unpack('<Q',pe+48)[0];sections=[]
    for i in range(count):
        at=pe+24+optional_size+i*40;name=r.take(at,8).rstrip(b'\0').decode('ascii','replace')
        virtual_size,rva,size,raw=r.unpack('<IIII',at+8);r.take(raw,size)
        sections.append(dict(name=name,va=imagebase+rva,file_offset=raw,file_size=size,virtual_size=virtual_size))
    def executable_va(va):
        return any(s['name']=='.text' and s['va']<=va<s['va']+s['file_size'] for s in sections)
    build=data.find(b'\xff Go buildinf:')
    if build<0 or r.take(build+14,2)!=b'\x08\x02':raise ValueError('Unsupported Go build info encoding')
    version,end=r.gostring(build+32);module,end=r.gostring(end)
    if len(module)<32:raise ValueError('Invalid Go module metadata')
    module=module[16:-16].decode('utf-8');version=version.decode('ascii')
    candidates=[]
    for m in re.finditer(b'\xf1\xff\xff\xff\x00\x00\x01\x08',data):
        values=r.unpack('<8Q',m.start()+8)
        if 0<values[0]<500000 and executable_va(values[2]):candidates.append((m.start(),values))
    if len(candidates)!=1:raise ValueError('Expected exactly one valid Go 1.20+ pclntab')
    start,(nfunc,nfiles,text,names,cu,files,pctab,pcln)=candidates[0]
    if not 72<=names<=cu<=files<=pctab<=pcln:raise ValueError('Invalid pclntab offsets')
    r.take(start+pcln,nfunc*8+4)
    functions=[]
    for i in range(nfunc):
        entry,info=r.unpack('<II',start+pcln+i*8);nextentry=r.unpack('<I',start+pcln+(i+1)*8)[0]
        first,name=r.unpack('<II',start+pcln+info)
        if first!=entry or nextentry<entry or not executable_va(text+entry) or name>=cu-names:raise ValueError('Invalid function metadata')
        functions.append(dict(address=hex(text+entry),name=r.string(start+names+name,cu-names-name),bytes=nextentry-entry))
    application=[f for f in functions if f['name'].startswith(('gommo/','main.'))]
    core=[f for f in application if f['name'].startswith(CORE)]
    packages=Counter(f['name'].split('.')[0] for f in application)
    file_names=r.take(start+files,pctab-files).split(b'\0')[:nfiles]
    source_files=[s.decode('utf-8','replace') for s in file_names]
    metadata=dict(source='gommostudio.exe',bytes=len(data),sha256=hashlib.sha256(data).hexdigest(),
                  format='Windows x86-64 PE32+',go_version=version,sections=sections,
                  build_info_offset=hex(build),pclntab_offset=hex(start),functions=len(functions),
                  application_functions=len(application),rf_format_functions=len(core),source_file_count=nfiles,
                  caveats=['Function names are retained Go metadata, not original source bodies.',
                           'Metadata indicates compiled modules, not verification that all features work.',
                           'The executable is never run by this inspector.'])
    return metadata,module,functions,application,core,dict(sorted(packages.items())),source_files


def zipped_json(path,value):
    with path.open('wb') as f:
        with gzip.GzipFile(filename='',mode='wb',fileobj=f,mtime=0) as z:
            z.write((json.dumps(value,separators=(',',':'))+'\n').encode())


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('binary',type=Path)
    parser.add_argument('--output',type=Path,default=Path(__file__).resolve().parents[1]/'analysis')
    args=parser.parse_args();values=inspect(args.binary.read_bytes());meta,module,functions,app,core,packages,files=values
    out=args.output;out.mkdir(parents=True,exist_ok=True)
    for name,data in [('metadata',meta),('packages',packages),('rf-format-functions',core)]:
        (out/(name+'.json')).write_text(json.dumps(data,indent=2)+'\n')
    zipped_json(out/'go-functions.json.gz',functions);zipped_json(out/'application-functions.json.gz',app)
    (out/'build-info.txt').write_text(meta['go_version']+'\n'+'\n'.join(line.rstrip() for line in module.splitlines())+'\n')
    (out/'source-files.txt').write_text('\n'.join(files)+'\n')
    print(json.dumps({k:meta[k] for k in ('bytes','sha256','go_version','functions','application_functions','rf_format_functions')}))


if __name__=='__main__':main()
