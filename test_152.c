#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    long int left;
    long int right;
} Interval;

// 按右端点排序
int compareIntervals(const void *p1, const void *p2) {
    Interval *a1 = (Interval*)p1;
    Interval *a2 = (Interval*)p2;
    if (a1->right != a2->right) {
        return a1->right - a2->right;
    }
    return a2->left - a1->left;
}

int maxNonOverlappingIntervals(Interval *intervals, long int n) {
    if (n <= 0) return 0;
    
    qsort(intervals, n, sizeof(Interval), compareIntervals);
    
    int count = 1;
    long int currentEnd = intervals[0].right;
    
    for (long int i = 1; i < n; i++) {
        if (intervals[i].left >= currentEnd) {
            count++;
            currentEnd = intervals[i].right;
        }
    }
    
    return count;
}

int main() {
    long int n;
    scanf("%ld", &n);
    
    // 动态分配内存
    Interval *intervals = (Interval*)malloc(n * sizeof(Interval));
    if (intervals == NULL) {
        return 1;
    }
    
    // 输入数据
    for (long int i = 0; i < n; i++) {
        scanf("%ld %ld", &intervals[i].left, &intervals[i].right);
    }
    
    // 计算结果
    int result = maxNonOverlappingIntervals(intervals, n);
    printf("%ld\n", result);
    
    free(intervals);
    return 0;
}
