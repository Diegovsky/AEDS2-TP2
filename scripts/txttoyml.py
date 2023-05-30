#!/usr/bin/env python3
import sys
import pathlib

def make(fname):
    yamlstr = ''
    with open(fname, 'r') as f:
        lines = []
        for l in f.readlines():
            if len(l) < 1:
                continue
            if l.startswith('Cmp') or l.startswith('Swap'):
                continue
            if l[0] == 'N':
                l = ' - ' + l
            else:
                l = '   ' + l.replace('Media ', '').lower()
            lines.append(l)
        yamlstr = ''.join(lines)

    with open(pathlib.PurePath(fname).with_suffix('.yaml'), 'w') as f:
        f.write(yamlstr)

for fname in sys.argv[1:]:
    make(fname)
