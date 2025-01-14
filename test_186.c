#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int64_t count0 = 0, count1 = 0, count2 = 0;
    int64_t result = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            count0++;
        } else if (arr[i] == 1) {
            count1 += count0;
        } else if (arr[i] == 2) {
            result += count1;
        }
    }
    
    printf("%lld\n", result);
    
    free(arr);
    return 0;
}