#include <stdio.h>

// 扩展欧几里得算法，返回 gcd(a, b)，并通过指针返回 x 和 y 的值
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1; // 用于保存递归返回的 x 和 y
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    int a, m;
    scanf("%d %d", &a, &m);

    int x, y;
    int gcd = extended_gcd(a, m, &x, &y);

    // 检查是否存在逆元
    if (gcd != 1) {
        printf("No Solution\n");
        return 0;
    }

    // 将 x 调整到范围 [0, m)
    x = (x % m + m) % m;

    printf("%d\n", x);
    return 0;
}
