#include <stdio.h>
#include <string.h>

// 递归函数，计算所有插入加号方式的结果之和
void calculateSum(char *num, int index, long long currentSum, long long currentNum, long long *totalSum) {
    int len = strlen(num);
    if (index == len) {
        *totalSum += currentSum + currentNum;
        return;
    }

    // 不插入加号，继续累加当前数字
    calculateSum(num, index + 1, currentSum, currentNum * 10 + (num[index] - '0'), totalSum);

    // 插入加号，计算当前部分的和
    calculateSum(num, index + 1, currentSum + currentNum, num[index] - '0', totalSum);
}

int main() {
    char num[9];
    scanf("%s", num);

    long long totalSum = 0;
    calculateSum(num, 1, 0, num[0] - '0', &totalSum);

    printf("%lld\n", totalSum);

    return 0;
}