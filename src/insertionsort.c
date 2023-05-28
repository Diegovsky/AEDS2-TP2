#include "runner.h"

void insertionsort(Item arr[], int n, long *num_comp, long *num_swap)
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

int main(int argc, char *argv[])
{
    time_execution(argc, argv, insertionsort);
}
