#pragma once

typedef int ChaveTipo;
typedef struct {
    ChaveTipo chave;
    char ext[50][50];
} Item;

typedef void (*FuncaoOrdenacao)(Item *arr, int n, long *comparacoes, long *trocas);

void swap(Item *a, Item *b);

void time_execution(int argc, char* argv[], FuncaoOrdenacao funcao);
