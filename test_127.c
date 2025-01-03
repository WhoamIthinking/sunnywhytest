#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int a[5000][12];

// 生成子集
void generate(int n, int b[]) {
    int i = 0;
    int j;
    for (i = 0; i < pow(2, n); i++) {
        for (j = 0; j < n; j++) {
            if (i & (1 << j)) {
                a[i][j] = b[j];
            } else {
                a[i][j] = 0; // 确保未选中的元素为0
            }
        }
    }
}

// 比较函数，用于qsort排序
int compare(const void *p1, const void *p2) {
    int *arrA = (int *)p1;
    int *arrB = (int *)p2;
    int sizeA = 0, sizeB = 0;

    // 计算子集的大小
    for (int i = 0; i < 12; i++) {
        if (arrA[i] != 0) sizeA++;
        if (arrB[i] != 0) sizeB++;
    }

    // 按子集大小排序
    if (sizeA != sizeB) return sizeA - sizeB;

    // 如果大小相同，按字典序排序
    for (int i = 0; i < 12; i++) {
        if (arrA[i] != arrB[i]) return arrB[i] - arrA[i];
    }

    return 0;
}

// 排序函数
void mysort(int n) {
    qsort(a, (int)pow(2, n), sizeof(a[0]), compare);
}

int main() {
    int n;
    scanf("%d", &n);
    int i = 0, j = 0;

    // 初始化数组a
    for (i = 0; i < pow(2, n); i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }

    // 读取输入的n个整数
    int *b = (int *)malloc(sizeof(int) * n);
    for (j = 0; j < n; j++) {
        scanf("%d", &b[j]);
    }

    // 生成子集
    generate(n, b);
    // 排序子集
    mysort(n);

    // 打印不重复的子集
    int *last = NULL;
    for (i = 0; i < pow(2, n); i++) {
        int *c=(int *)malloc(sizeof(int)*n);
        for(j=0;j<n;j++){
            c[j]=0;
        }
        int k=0;
        int first = 1; // 标记是否是第一个元素
        for (j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                c[k]=a[i][j];
                k++;
            }
        }
        if(last!=NULL&&compare(c,last)==0){
            last=c;
            continue;
        }
        for(j=0;j<k;j++){
            if(j==0){
                printf("%d",c[j]);
            }
            else{
                printf(" %d",c[j]);
            }
        }
        free(last);
        last = c;
        printf("\n");
    }

    free(b);
    return 0;
}
