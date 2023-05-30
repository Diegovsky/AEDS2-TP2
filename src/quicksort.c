#include "runner.h"

int partition(Item* array, int low, int high, long* num_cmp, long* num_swap) {

    ChaveTipo pivot = array[high].chave;
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        (*num_cmp)++;
        if (array[j].chave <= pivot) {
            i++;
            (*num_swap)++;
            swap(&array[i], &array[j]);
        }
    }

    (*num_swap)++;
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quicksort(Item* array, int low, int high, long* num_cmp, long* num_swap) {
    if (low < high) {

        int pi = partition(array, low, high, num_cmp, num_swap);

        quicksort(array, low, pi - 1, num_cmp, num_swap);

        quicksort(array, pi + 1, high, num_cmp, num_swap);
    }
}

// Para ser chamada pela função time_execution, que exige um formato específico
// de argumentos
void quicksort_(Item* array, int n, long* num_cmp, long* num_swap) {
    quicksort(array, 0, n - 1, num_cmp, num_swap);
}

int main(int argc, char *argv[])
{
    time_execution(argc, argv, quicksort_);
}
