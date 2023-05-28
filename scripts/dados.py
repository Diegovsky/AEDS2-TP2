#!/usr/bin/python3

import yaml
import sys

if len(sys.argv) == 1:
    print("Uso: python dados.py <arquivo>")
    sys.exit(1)

file = sys.argv[1]
file = open(file, 'r')
file = file.read()
file = file.replace('\t', '  ')
stats = yaml.full_load(file)

def mean_of(runs: list[dict], attr: str) -> float:
    return sum([run[attr] for run in runs]) / len(runs)

def printrepeat_of(runs: list[dict], attr: str) -> None:
    isrep = all([run[attr] == runs[0][attr] for run in runs])
    txt = isrep and 'é' or 'não é'
    print(f'{attr} {txt} constante')

def printmean_of(runs: list[dict], attr: str) -> None:
    print(f'Media {attr}: {mean_of(runs, attr):.6f}')

try:
    runs = stats['Runs']
except TypeError:
    print("Detected invalid YAML file in ", sys.argv[1])
    sys.exit(1)


print('N: ', stats['N'])
printmean_of(runs, 'Time')
printmean_of(runs, 'Cmp')
printmean_of(runs, 'Swap')

printrepeat_of(runs, 'Cmp')
printrepeat_of(runs, 'Swap')
