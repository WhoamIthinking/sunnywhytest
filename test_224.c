#include <stdio.h>

// 扩展欧几里得算法
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    int x, y;
    int gcd = extended_gcd(a, b, &x, &y);
    
    // 调整 x 和 y 使得 x 最小且非负
    int k = (x < 0) ? (-x + b - 1) / b : 0;
    x += k * b;
    y -= k * a;
    
    printf("%d %d\n", x, y);
    
    return 0;
}