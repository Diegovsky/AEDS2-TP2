#include "runner.h"

void heapify(Item *arr, int n, int i, long* num_cmp, long* num_swap) {
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

void heapsort(Item *arr, int n, long* num_cmp, long* num_swap) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, num_cmp, num_swap);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        (*num_swap)+=3;
        heapify(arr, i, 0, num_cmp, num_swap);
    }
}

int main(int argc, char *argv[])
{
    time_execution(argc, argv, heapsort);
}
