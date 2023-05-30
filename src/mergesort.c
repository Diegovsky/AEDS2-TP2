#include <stdlib.h>
#include "runner.h"

void merge(Item arr[], int l, int m, int r, long* num_comp, long* num_swap)
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

void mergesort(Item arr[], int l, int r, long* num_comp, long* num_swap)
{   
    (*num_comp)++;
    if (l < r) {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m, num_comp, num_swap);
        mergesort(arr, m + 1, r, num_comp, num_swap);
        merge(arr, l, m, r, num_comp, num_swap);
    }
}

// Para ser chamada pela função time_execution, que exige um formato específico
// de argumentos
void mergesort_(Item* array, int n, long* num_cmp, long* num_swap) {
    mergesort(array, 0, n - 1, num_cmp, num_swap);
}


int main(int argc, char *argv[])
{
    time_execution(argc, argv, mergesort_);
}
