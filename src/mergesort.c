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
    // char ext[50][50];
} Item;

void merge(Item arr[], int l, int m, int r, int *num_comp, int *num_swap)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Item* L = malloc(n1*sizeof(Item));
    Item* R = malloc(n2*sizeof(Item));


    (*num_swap) += n1;
    for (i = 0; i < n1; i++)
        L[i].chave = arr[l + i].chave;
        
    (*num_swap) += n2;
    for (j = 0; j < n2; j++)
        R[j].chave = arr[m + 1 + j].chave;

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        (*num_comp)++;
        if (L[i].chave <= R[j].chave) {
            (*num_swap)++;
            arr[k].chave = L[i].chave;
            i++;
        }
        else {
            (*num_swap)++;
            arr[k].chave = R[j].chave;
            j++;
        }
        k++;
    }

    while (i < n1) {
        (*num_swap)++;
        arr[k].chave = L[i].chave;
        i++;
        k++;
    }

    while (j < n2) {
        (*num_swap)++;
        arr[k].chave = R[j].chave;
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(Item arr[], int l, int r, int *num_comp, int *num_swap)
{   
    (*num_comp)++;
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, num_comp, num_swap);
        mergeSort(arr, m + 1, r, num_comp, num_swap);
        merge(arr, l, m, r, num_comp, num_swap);
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
    mergeSort(arr, 0, n - 1, &num_cmp, &num_swap);

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
