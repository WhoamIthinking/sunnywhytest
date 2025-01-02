#include<stdio.h>

// 递归函数，计算分解方案数
int countWays(int n, int min) {
    if (n == 0) return 1; // 如果 n 为 0，表示找到一种有效的分解方案
    int count = 0;
    for (int i = min; i <= n; i++) { // 从 min 开始尝试分解 n
        count += countWays(n - i, i); // 递归调用，继续分解剩余的 n - i
    }
    return count; // 返回分解方案数
}

int main() {
    int n;
    //printf("请输入一个正整数: ");
    scanf("%d", &n); // 输入一个正整数
    if (n <= 1) {
        printf("没有方案\n"); // 如果 n 小于等于 1，则没有有效的分解方案
    } else {
        // 减去1是因为至少要两个正整数之和
        printf("%d\n", countWays(n, 1) - 1); // 计算并输出分解方案数
    }
    return 0;
}
