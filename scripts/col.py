#!/usr/bin/env python3
import sys
import yaml
import os
import pathlib

sdir = os.path.dirname(os.path.realpath(__file__))
tbl = sdir+'/tbl.html'

if len(sys.argv) <= 1:
    print('Usage: col.py <big.yaml> <small.yaml> <time>')
    exit(-1)

def load_yaml(path: str) -> list[dict]:
    p = pathlib.Path(path)
    if path.endswith('.txt'):
        os.system('python3 scripts/txttoyml.py '+path)
        p = pathlib.Path(path[:-4]+'.yaml')
    with open(p, 'r') as f:
        return yaml.safe_load(f)

big_data = load_yaml(sys.argv[1])
small_data = load_yaml(sys.argv[2])

attr = sys.argv[3]

with open(tbl, 'r') as f:
    template = f.read()

j = [[small[attr], big[attr]] for big, small in zip(big_data, small_data)]
j = [item for sublist in j for item in sublist]

print(template.format(*j))
