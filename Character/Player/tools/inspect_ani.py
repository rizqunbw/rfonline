"""Read RF ANI object tracks without applying skeleton/coordinate transforms.

Layout reference: cbb-rf-online-addon (MIT); ../THIRD_PARTY_LICENSE.txt.
Time values are retained as ticks. The reference uses 160 ticks per frame;
seconds/FPS cannot be established from this header alone.
"""
import argparse
import json
import math
from pathlib import Path
import struct


def inspect(data, include_keys=False):
    cursor=0
    def take(n):
        nonlocal cursor
        if n<0 or cursor+n>len(data):raise ValueError(f'Truncated ANI at offset {cursor}')
        out=data[cursor:cursor+n];cursor+=n;return out
    def read(fmt):return struct.unpack('<'+fmt,take(struct.calcsize('<'+fmt)))
    count,=read('H')
    if count>(len(data)-2)//148:raise ValueError('Invalid ANI object count')
    objects=[];totals=dict(rotation=0,position=0,scale=0,scalar=0);last_tick=0
    for _ in range(count):
        name=take(100).split(b'\0',1)[0].decode('euc-kr')
        enabled,duration=read('HH');take(36)
        obj={'name':name,'activityField':enabled,'declaredEndTick':duration,'tracks':{}}
        last_tick=max(last_tick,duration)
        for channel,width in [('rotation',4),('position',3),('scale',3),('scalar',1)]:
            n,=read('H');values=[];times=[]
            for _ in range(n):
                record=read(f'{width}fI');value=record[:-1];tick=record[-1]
                if not all(math.isfinite(v) for v in value):raise ValueError(f'Nonfinite {channel} key in {name}')
                times.append(tick)
                if include_keys:values.append({'tick':tick,'value':list(value)})
            track={'keys':n,'firstTick':min(times) if times else None,'lastTick':max(times) if times else None,
                   'nondecreasing':all(a<=b for a,b in zip(times,times[1:]))}
            if include_keys:track['values']=values
            obj['tracks'][channel]=track;totals[channel]+=n
            if times:last_tick=max(last_tick,max(times))
        objects.append(obj)
    if cursor!=len(data):raise ValueError(f'Unparsed trailing bytes: {len(data)-cursor}')
    return {'objectCount':count,'keyCounts':totals,'endTick':last_tick,'bytesConsumed':cursor,'objects':objects}


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('animation',type=Path);p.add_argument('--keys',action='store_true')
    args=p.parse_args();print(json.dumps(inspect(args.animation.read_bytes(),args.keys),indent=2))
