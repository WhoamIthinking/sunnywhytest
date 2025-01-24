#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int size;
} BigInt;

BigInt toBigInt(char *nums) {
    BigInt result;
    int len = strlen(nums);
    result.data = (int *)malloc(len * sizeof(int));
    result.size = len;
    for (int i = 0; i < len; i++) {
        result.data[i] = nums[len - 1 - i] - '0';
    }
    return result;
}

BigInt div(BigInt a, int b, int *r) {
    BigInt c;
    c.data = (int *)malloc(a.size * sizeof(int));
    c.size = 0;
    *r = 0;
    for (int i = a.size - 1; i >= 0; i--) {
        *r = *r * 10 + a.data[i];
        c.data[c.size++] = *r / b;
        *r = *r % b;
    }
    for (int i = 0; i < c.size / 2; i++) {
        int temp = c.data[i];
        c.data[i] = c.data[c.size - 1 - i];
        c.data[c.size - 1 - i] = temp;
    }
    while (c.size > 1 && c.data[c.size - 1] == 0) {
        c.size--;
    }
    return c;
}

void print(BigInt a) {
    for (int i = a.size - 1; i >= 0; i--) {
        printf("%d", a.data[i]);
    }
}

int main() {
    char nums[1001];
    int b, r = 0;
    scanf("%s %d", nums, &b);
    if (b == 0) {
        printf("undefined");
        return 0;
    }
    BigInt a = toBigInt(nums);
    BigInt q = div(a, b, &r);
    print(q);
    printf(" %d", r);
    free(a.data);
    free(q.data);
    return 0;
}