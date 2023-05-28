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

void heapify(Item *arr, int n, int i, int* num_cmp, int* num_swap) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    (*num_cmp)++;
    if (left < n && arr[left].chave > arr[largest].chave)
        largest = left;

    (*num_cmp)++;
    if (right < n && arr[right].chave > arr[largest].chave)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        (*num_swap)+=3;
        heapify(arr, n, largest, num_cmp, num_swap);
    }
}

void heapSort(Item *arr, int n, int* num_cmp, int* num_swap) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, num_cmp, num_swap);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        (*num_swap)+=3;
        heapify(arr, i, 0, num_cmp, num_swap);
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
    int num_cmp = 0;
    int num_swap = 0;
    struct timeval end, start;
    gettimeofday(&start, ((void *)0));

    // coloque aqui sua função de ordenação
    heapSort(arr, n, &num_cmp, &num_swap);

    gettimeofday(&end, ((void *)0));
    double time = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
    print("- Cmp", num_cmp, "%d");
    print("  Swap", num_swap, "%d");
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
