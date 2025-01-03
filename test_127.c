#include <stdio.h>
#include <stdlib.h>

// 打印子集
void printSubset(int *subset, int subsetSize) {
    for (int i = 0; i < subsetSize; i++) {
        if (i > 0) printf(" ");
        printf("%d", subset[i]);
    }
    printf("\n");
}

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    int *arrA = *(int **)a;
    int *arrB = *(int **)b;
    int sizeA = arrA[0];
    int sizeB = arrB[0];

    // 按子集大小排序
    if (sizeA != sizeB) return sizeA - sizeB;

    // 如果大小相同，按字典序排序
    for (int i = 1; i <= sizeA && i <= sizeB; i++) {
        if (arrA[i] != arrB[i]) return arrA[i] - arrB[i];
    }

    return 0;
}

int main() {
    int n;
    // 读取输入的整数n
    scanf("%d", &n);

    // 动态分配数组arr，存储1到n的整数
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // 计算所有子集的总数
    int totalSubsets = 1 << n;
    // 动态分配二维数组subsets，存储所有子集
    int **subsets = (int **)malloc(totalSubsets * sizeof(int *));
    int subsetIndex = 0;

    // 生成所有子集
    for (int i = 0; i < totalSubsets; i++) {
        int *subset = (int *)malloc((n + 1) * sizeof(int));
        subset[0] = 0; // 子集的大小存储在第一个元素
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset[++subset[0]] = arr[j];
            }
        }
        subsets[subsetIndex++] = subset;
    }

    // 对所有子集进行排序
    qsort(subsets, totalSubsets, sizeof(int *), compare);

    // 打印所有子集并释放内存
    for (int i = 0; i < totalSubsets; i++) {
        printSubset(subsets[i] + 1, subsets[i][0]);
        free(subsets[i]);
    }

    free(subsets);
    free(arr);

    return 0;
}