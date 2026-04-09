#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// 【修改處】在此修改 N 的值，例如 1000, 10000, 20000 進行實驗 [cite: 13, 138]
#define N 10000 

// --- 排序演算法區 (在此加入五種排序法) ---

void bubble_sort(int a[], int n) {
    for (int k = n - 1; k > 0; k--) {
        for (int i = 0; i < k; i++) {
            if (a[i] > a[i + 1]) {
                int t = a[i]; a[i] = a[i + 1]; a[i + 1] = t;
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
        int t = a[min_idx]; a[min_idx] = a[i]; a[i] = t;
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

// 快速排序與合併排序的遞迴實作... (略，請參考前一則回應)

// --- 實驗核心邏輯 ---

int main() {
    int data[N];
    clock_t start, end;
    double time_used;

    // 1. 初始化為完全逆序 (最差情況) [cite: 6, 71, 91]
    for (int i = 0; i < N; i++) data[i] = N - i;

    printf("實驗參數: N = %d\n", N);
    printf("--------------------------------------\n");

    // 以氣泡排序為例的測量流程 [cite: 6, 101, 107]
    int *temp = (int*)malloc(N * sizeof(int));
    memcpy(temp, data, N * sizeof(int));
    
    start = clock(); // 計時開始 [cite: 102]
    bubble_sort(temp, N);
    end = clock(); // 計時結束 [cite: 107]
    
    time_used = (double)(end - start) / CLOCKS_PER_SEC; // 換算成秒 [cite: 6, 115]
    printf("氣泡排序花費時間 = %.4f 秒\n", time_used); [cite: 113, 127]

    free(temp);
    return 0;
}