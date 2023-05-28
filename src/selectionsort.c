#include "runner.h"

void selectionsort(Item arr[], int n, long *num_comp, long *num_swap)
{
    int i, j, min_idx;
    *num_comp = 0;

    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
        {
            (*num_comp)++;
            if (arr[j].chave < arr[min_idx].chave)
            {
                min_idx = j;
            }
        }
        (*num_swap)+=3;
        swap(&arr[min_idx], &arr[i]);
    }
}

int main(int argc, char *argv[])
{
    time_execution(argc, argv, selectionsort);
}
