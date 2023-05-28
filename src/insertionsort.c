#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

void error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

typedef int ChaveTipo;
typedef struct {
    ChaveTipo chave;
    char ext[50][50];
} Item;

void swap(Item *a, Item *b) {
  Item t = *a;
  *a = *b;
  *b = t;
}

void insertionSort(Item arr[], int n, long *num_comp, long *num_swap)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i].chave;
        j = i - 1;

        while (j >= 0 && arr[j].chave > key) {
            (*num_comp)++;
            arr[j + 1].chave = arr[j].chave;
            (*num_swap)++;
            j = j - 1;
        }
        (*num_comp)++;
        arr[j + 1].chave = key;
        (*num_swap)++;
    }
}


#define print(label, val, type) printf("\t"label": "type"\n", val)

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

void run_sort_print_stats(int n, int order) {
    Item* arr;
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
    struct timeval end, start;
    gettimeofday(&start, ((void *)0));

    // coloque aqui sua função de ordenação
    insertionSort(arr, n, &num_cmp, &num_swap);

    gettimeofday(&end, ((void *)0));
    double time = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
    print("- Cmp", num_cmp, "%ld");
    print("  Swap", num_swap, "%ld");
    print("  Time", time, "%lf");
    printf("\n");
    free(arr);
}

void main_auto(int argc, char const *argv[]) {
    if(argc == 2) {
        error("Faltam argumentos");
        return;
    }
    int n;
    if(sscanf(argv[1], "%d", &n) != 1) {
        error("Número inválido");
        return;
    }
    char order_str[50];
    if(sscanf(argv[2], "%s", order_str) != 1) {
        error("Não entendi");
        return;
    }
    int order;
    if (strcmp(order_str, "rand") == 0) order = 0; 
    else if (strcmp(order_str, "cres") == 0) order = 1; 
    else if (strcmp(order_str, "decres") == 0) order = 2; 
    else {
        error("Ordenação invalida");
        return;
    }
    printf("N: %d\nRuns:\n", n);
    for(int i = 0; i < 10; i++) {
        run_sort_print_stats(n, order);
    }
}



int main(int argc, char const *argv[]) {
    if(argc == 1) return -1;
    struct timeval st;
    gettimeofday(&st, NULL);
    srand(st.tv_usec);
    main_auto(argc, argv);
    return 0;
}
