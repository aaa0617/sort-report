#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

void bubble_sort(int a[], int n) {
    for (int k = n - 1; k > 0; k--) {
        for (int i = 0; i < k; i++) {
            if (a[i] > a[i + 1]) {
                int t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
            }
        }
    }
}

void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        int t = a[min_idx];
        a[min_idx] = a[i];
        a[i] = t;
    }
}

void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void merge(int a[], int left, int mid, int right, int temp[]) {
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (i = left; i <= right; i++) {
        a[i] = temp[i];
    }
}

void merge_sort_recursive(int a[], int left, int right, int temp[]) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_recursive(a, left, mid, temp);
    merge_sort_recursive(a, mid + 1, right, temp);
    merge(a, left, mid, right, temp);
}

void merge_sort(int a[], int n) {
    int *temp = malloc(n * sizeof(int));
    if (temp == NULL) return;
    merge_sort_recursive(a, 0, n - 1, temp);
    free(temp);
}

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    int t = a[i + 1];
    a[i + 1] = a[high];
    a[high] = t;
    return i + 1;
}

void quick_sort_recursive(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quick_sort_recursive(a, low, pi - 1);
        quick_sort_recursive(a, pi + 1, high);
    }
}

void quick_sort(int a[], int n) {
    quick_sort_recursive(a, 0, n - 1);
}

void measure_sort(void (*sort_func)(int *, int), const char *name, int data[], int n) {
    int *temp = malloc(n * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "記憶體配置失敗\n");
        return;
    }
    memcpy(temp, data, n * sizeof(int));

    clock_t start = clock();
    sort_func(temp, n);
    clock_t end = clock();

    double time_used = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%-15s: %.6f 秒\n", name, time_used);

    free(temp);
}

int main() {
    int data[N];
    for (int i = 0; i < N; i++) {
        data[i] = N - i;
    }

    printf("實驗參數: N = %d\n", N);
    printf("--------------------------------------\n");

    measure_sort(bubble_sort, "Bubble Sort", data, N);
    measure_sort(selection_sort, "Selection Sort", data, N);
    measure_sort(insertion_sort, "Insertion Sort", data, N);
    measure_sort(merge_sort, "Merge Sort", data, N);
    measure_sort(quick_sort, "Quick Sort", data, N);

    return 0;
}
