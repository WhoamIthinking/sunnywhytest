#include <stdio.h>

// 计算 n! 中包含质因子 p 的个数
int count_factor_in_factorial(int n, int p) {
    int count = 0;
    while (n > 0) {
        n /= p;
        count += n;
    }
    return count;
}

// 分解 m 为质因子并计算 n! 中包含 m 的个数
int count_factors(int n, int m) {
    int count = 0;
    for (int i = 2; i * i <= m; i++) {
        if (m % i == 0) {
            int current_count = 0;
            while (m % i == 0) {
                m /= i;
                current_count++;
            }
            int factor_count = count_factor_in_factorial(n, i) / current_count;
            if (count == 0 || factor_count < count) {
                count = factor_count;
            }
        }
    }
    if (m > 1) {
        int factor_count = count_factor_in_factorial(n, m);
        if (count == 0 || factor_count < count) {
            count = factor_count;
        }
    }
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int result = count_factors(n, m);
    printf("%d\n", result);
    return 0;
}