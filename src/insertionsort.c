#include "runner.h"

void insertionsort(Item *arr, int n, long *num_comp, long *num_swap)
{
    int i, j;
    Item key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        (*num_swap)++;
        j = i - 1;

        while (j >= 0 && arr[j].chave > key.chave) {
            (*num_comp)++;
            arr[j + 1]= arr[j];
            (*num_swap)++;
            j = j - 1;
        }
        (*num_comp)++;
        arr[j + 1]= key;
        (*num_swap)++;
    }
}

int main(int argc, char *argv[])
{
    time_execution(argc, argv, insertionsort);
}
