"""Browse the native decompilation without printing the entire client to a tool/chat.

Examples:
  python System/tools/read_decompiled.py --search KeyMap --limit 5
  python System/tools/read_decompiled.py --function 00538c00 --output /tmp/function.c
"""
import argparse
import gzip
import json
import re
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]


def functions(path):
    address=None;lines=[]
    with gzip.open(path,'rt',encoding='utf-8') as f:
        for line in f:
            marker=re.fullmatch(r'/\* FUNCTION ([0-9a-fA-F]+) \*/\n',line)
            if marker:
                if address:yield address,''.join(lines)
                address=marker[1];lines=[]
            elif address:lines.append(line)
    if address:yield address,''.join(lines)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    modes=parser.add_mutually_exclusive_group(required=True)
    modes.add_argument('--search');modes.add_argument('--function')
    parser.add_argument('--limit',type=int,default=10)
    parser.add_argument('--output',type=Path)
    args=parser.parse_args()
    if not 1<=args.limit<=100:parser.error('--limit must be 1..100')
    archive=ROOT/'System/analysis/decompiled/client-decompiled.c.gz'
    if args.function:
        try:wanted=f'{int(args.function,16):08x}'
        except ValueError:parser.error('Function address must be hexadecimal')
        for address,code in functions(archive):
            if address.lower()==wanted:
                if args.output:
                    args.output.write_text(code);print(f'{address}: {len(code)} characters -> {args.output}')
                else:
                    print(code[:12000])
                    if len(code)>12000:print('\n[Output capped at 12,000 characters. Use --output for the entire function.]')
                return
        parser.error('Function not present in this analysis')
    else:
        count=0
        for address,code in functions(archive):
            if args.search.casefold() not in code.casefold():continue
            matches=[line.strip()[:180] for line in code.splitlines() if args.search.casefold() in line.casefold()]
            print(json.dumps({'address':address,'characters':len(code),'matches':matches[:3]}))
            count+=1
            if count==args.limit:break
        print(f'Showing {count} result(s), limit {args.limit}.')


if __name__=='__main__':main()
