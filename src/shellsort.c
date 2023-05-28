#include "runner.h"

void shellsort(Item arr[], int num, long *num_comp , long *num_swap) {
    int i, j, k, tmp;
    for (i = num / 2; i > 0; i = i / 2) {
        for (j = i; j < num; j++) {
            for(k = j - i; k >= 0; k = k - i) {
                if (arr[k+i].chave >= arr[k].chave)
                {
                    (*num_comp)++;
                    break;
                }
                else {
                    tmp = arr[k].chave;
                    arr[k].chave = arr[k+i].chave;
                    arr[k+i].chave = tmp;
                    (*num_swap)++;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    time_execution(argc, argv, shellsort);
}
