"""Search Go symbols and extract bounded decompiler output without running the editor."""
import argparse
import gzip
import json
from pathlib import Path
import re

ROOT=Path(__file__).resolve().parents[1]/'analysis'


def functions():
    address=None;name=None;lines=[]
    with gzip.open(ROOT/'application-decompiled.c.gz','rt') as f:
        for line in f:
            marker=re.fullmatch(r'/\* FUNCTION (0x[0-9a-fA-F]+) (.*) \*/\n',line)
            if marker:
                if address:yield address,name,''.join(lines)
                address,name=marker[1],marker[2];lines=[]
            elif address:lines.append(line)
    if address:yield address,name,''.join(lines)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    mode=parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--search');mode.add_argument('--function')
    parser.add_argument('--limit',type=int,default=10);parser.add_argument('--output',type=Path)
    args=parser.parse_args()
    if not 1<=args.limit<=100:parser.error('limit must be 1..100')
    if args.search:
        with gzip.open(ROOT/'go-functions.json.gz','rt') as f:index=json.load(f)
        rows=[r for r in index if args.search.casefold() in r['name'].casefold()]
        for row in rows[:args.limit]:print(json.dumps(row))
        print(f'{len(rows)} matches; showing at most {args.limit}.')
        return
    for address,name,code in functions():
        if args.function.casefold() not in (address.casefold(),name.casefold()):continue
        if args.output:args.output.write_text(code);print(f'{name}: {len(code)} characters -> {args.output}')
        else:
            print(code[:12000])
            if len(code)>12000:print('\n[Output capped. Use --output to save the whole function.]')
        return
    parser.error('Function is not present in the application pseudocode archive')


if __name__=='__main__':main()
