#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "runner.h"

void error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

void swap(Item *a, Item *b) {
  Item t = *a;
  *a = *b;
  *b = t;
}

void parse_args(int argc, char *argv[], long* n, long* order);
void save_time(int n, int order);

Item* rand_vec(size_t n) {
    Item* arr = malloc(n * sizeof(Item));
    if(arr == NULL) { perror("Malloc failed"); exit(-1); };
    for(size_t i = 0; i < n; i++) {
        arr[i].chave = rand();
    }
    return arr;
}

//vetor com valores crescentes
Item* cres_vec(size_t n) {
    Item* arr = malloc(n * sizeof(Item));
    if(arr == NULL) { perror("Malloc failed"); exit(-1); };
    for(size_t i = 0; i < n; i++) {
        arr[i].chave = i;
    }
    return arr;
}

//vetor valores decrescentes
Item* decres_vec(size_t n) {
    Item* arr = malloc(n * sizeof(Item));
    if(arr == NULL) { perror("Malloc failed"); exit(-1); };
    for(size_t i = 0; i < n; i++) {
        arr[i].chave = n - i;
    }
    return arr;
}

void time_execution(int argc, char* argv[], FuncaoOrdenacao f) {
    if(argc == 1) {
        error("Esperava argumentos");
    };
    struct timeval st;
    gettimeofday(&st, NULL);
    srand(st.tv_usec);

    long n, order;
    parse_args(argc, argv, &n, &order);

    Item* arr;
    printf("N: %ld\n"
           "Runs:\n", n);
    for(int i = 0; i < 10; i++) {
        switch (order) {
            case 0:
                arr = rand_vec(n);
                break;
            case 1:
                arr = cres_vec(n);
                break;
            case 2:
                arr = decres_vec(n);
                break;
        }
        long num_cmp = 0;
        long num_swap = 0;

        struct timeval start, end;

        gettimeofday(&start, ((void *)0));
        f(arr, n, &num_cmp, &num_swap);

        gettimeofday(&end, ((void *)0));
        double time = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
        #define print(label, val, type) printf("\t"label": "type"\n", val)

        print("- Cmp", num_cmp, "%ld");
        print("  Swap", num_swap, "%ld");
        print("  Time", time, "%lf");

        #undef print
        printf("\n");
        free(arr);
    }
}

void parse_args(int argc, char *argv[], long* n, long* order) {
    if(argc <= 2) {
        error("Faltam argumentos");
    } else if(argc > 3) {
        error("Argumentos demais");
    }
    if(sscanf(argv[1], "%ld", n) != 1) {
        error("Número inválido");
        return;
    }
    char order_str[50];
    if(sscanf(argv[2], "%s", order_str) != 1) {
        error("Não entendi a ordem");
        return;
    }
    if (strcmp(order_str, "rand") == 0) *order = 0; 
    else if (strcmp(order_str, "cres") == 0) *order = 1; 
    else if (strcmp(order_str, "decres") == 0) *order = 2; 
    else {
        error("Ordenação invalida");
        return;
    }
}
