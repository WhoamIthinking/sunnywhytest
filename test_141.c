#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_RESULT 6000
#define MAX_SIZE 12

int result[MAX_RESULT][MAX_SIZE];
int k = 0;
int sum = 0;

int compare1(const void *p1, const void *p2) {
    return (*(int*)p1 - *(int*)p2);
}

int compare(const void *p1, const void *p2) {
    int *arrA = (int *)p1;
    int *arrB = (int *)p2;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (arrA[i] != arrB[i]) return arrA[i] - arrB[i];
    }
    return 0;
}

void generatesum(int n, int m, int now, int arr[], int index, int *combo, int p) {
    if (now == m) {
        for (int i = 0; i < p; i++) {
            result[k][i] = combo[i];
        }
        qsort(result[k], p, sizeof(int), compare1);
        k++;
        return;
    }
    if (now > m || index >= n) return;

    // 包含当前元素的组合
    if (now + arr[index] <= m) {
        combo[p] = arr[index];
        generatesum(n, m, now + arr[index], arr, index, combo, p + 1);
        generatesum(n, m, now + arr[index], arr, index + 1, combo, p + 1);
    }

    // 不包含当前元素的组合
    generatesum(n, m, now, arr, index + 1, combo, p);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *arr = (int*)malloc(sizeof(int) * n);
    int *combo = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    generatesum(n, m, 0, arr, 0, combo, 0);

    qsort(result, k, sizeof(result[0]), compare);

    for (int i = 0; i < k; i++) {
        if (i > 0 && compare(result[i - 1], result[i]) == 0) {
            continue;
        }
        sum++;
    }

    printf("%d", sum);

    free(combo);
    free(arr);
    return 0;
}