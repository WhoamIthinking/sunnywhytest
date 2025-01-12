#include <stdio.h>
#include <stdlib.h>

int find_rotation(int arr[], int n) {
    int front = 0;
    int end = n - 1;
    while (front < end) {
        int middle = front + (end - front) / 2;
        if (arr[middle] <= arr[end]) {
            end = middle;
        } else {
            front = middle + 1;
        }
    }
    return arr[front];
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int min_element = find_rotation(arr, n);
    printf("%d\n", min_element);
    free(arr);
    return 0;
}