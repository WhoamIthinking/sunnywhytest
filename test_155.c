#include <stdio.h>

int find_peak(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int peak_index = find_peak(arr, n);
    printf("%d\n", peak_index);
    return 0;
}