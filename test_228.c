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
    int n,a, m;
    scanf("%d %d %d", &n,&a, &m);
    int x, y;
    int gcd = extended_gcd(a, m, &x, &y);
    // 将 x 调整到范围 [0, m)
    x = (x % m + m) % m;
    int mul=x;
    int b;
    for(int i=0;i<n;i++){
        scanf("%d",&b);
        mul=(mul*b)%m;
    }
    printf("%d",mul);
    return 0;
}
