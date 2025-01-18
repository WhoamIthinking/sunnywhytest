#include <stdio.h>
#include<math.h>
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
    int a, b, c;
    scanf("%d %d %d", &a, &c, &b);

    int x, y;
    int gcd = extended_gcd(a, b, &x, &y);

    // 检查是否有解
    if (c % gcd != 0) {
        printf("No Solution\n");
        return 0;
    }
    int p=c/gcd;
    int m1,m2;
    if(b/gcd<0){
        m1=-b/gcd;
        m2=-a/gcd;
    }
    else{
        m1=b/gcd;
        m2=a/gcd;
    }
    x=x*p;y=y*p;
    while(x<0){
        x=x+m1;
        y=y-m2;
    }
    while(x>=0){
        x=x-m1;
        y=y+m2;
    }
    x=x+m1;
    y=y-m2;
    printf("%d",x);
    return 0;
}
