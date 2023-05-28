#!/usr/bin/env python3
import sys
import yaml
import numpy as np
import matplotlib.pyplot as plt

def makeplot(fname, statname, algorithm, escala):
    x = []  # empty list to store the first column (x-axis)
    y = []  # empty list to store the third column (y-axis)


    yamlstr = ''
    try:
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
    except FileNotFoundError:
        print(f'Arquivo {fname} não encontrado')
        return None


    for stat in yaml.safe_load(yamlstr):
        x.append(stat['N'])
        y.append(stat[statname])

    statlabel = (({
        'time': 'Tempo de execução em segundos',
        'cmp': 'Quantidade de comparações',
        'swap': 'Quantidade de trocas'
    })[statname])

    # y = np.multiply(y, 1000)
    p = np.polyfit(x, y, 4)

    print(p)
    print(np.polyval(p, x))
    plt.plot(x, np.polyval(p, x), 'red', linewidth=2, label='Regressão Polinomial')
    plt.plot(x, y, 'o', markersize=4, label='Tempo decorrido')

    plt.xscale('log')
    plt.yscale(escala)
    plt.yticks(y, y)
    plt.xticks(x, x)
    plt.xlabel(f'Número de elementos ({escala})')
    plt.ylabel(f'{statlabel} ({escala})')

    sort = (({
        'rand': 'Aleatório',
        'cres': 'Crescente',
        'decres': 'Decrescente'
    })[fname.split('_')[0]])

    plt.title('{} - {}'.format(algorithm.title(), 'Ordenação Inicial ' + sort))

    plt.legend()
    plt.gcf().set_size_inches(10, 5)
    return plt




def getarg(n, msg):
    try:
        return sys.argv[n]
    except IndexError:
        print(msg)
        exit(-1)

def savegraph(plt, sort, attr):
    if plt is None:
        return
    plt.savefig(f'{sort}_{attr}.svg', dpi=160, orientation='landscape', bbox_inches='tight', pad_inches=0.1)
    plt.clf()


def genimages(algo):
    for sort in ['rand', 'cres', 'decres']:
        for attr in ['time', 'swap', 'cmp']:
            try:
                plt = makeplot(f'{sort}_report.txt', attr, algo, 'log')
                savegraph(plt, sort, attr)

            except ValueError:
                plt = makeplot(f'{sort}_report.txt', attr, algo, 'linear')
                savegraph(plt, sort, attr)

def showimage():
    fname = getarg(1, 'Esperava um argumento com o nome do arquivo')
    statname = getarg(2, 'Esperava um argumento com o nome da estatística')
    algorithm = getarg(3, 'Esperava um argumento com o nome do algoritmo')
    escala = getarg(4, 'Esperava um argumento com escala')
    makeplot(fname, statname, algorithm, escala).show()

try:
    algo = sys.argv[1]
except IndexError:
    algo = input('Digite o nome do algoritmo: ')

genimages(algo)
