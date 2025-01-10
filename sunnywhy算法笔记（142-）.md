# sunnywhy算法笔记（142-）

## 152——使用贪心算法求解区间个数

本题虽然题号上标了使用递归，但实际上使用递归是很慢的，当数据增大时时间复杂度会急剧上升，因此需要使用贪心算法，下面是使用递归的解法：

```c
#include<stdio.h>
#include<stdlib.h>
typedef struct Intervel{
    long int left;
    long int right;
}intervel;
intervel arr[15000];
int cmp(const void *p1,const void *p2){
    intervel *a1=(intervel*)p1;
    intervel *a2=(intervel*)p2;
    if(a1->left!=a2->left){
        return a1->left-a2->left;
    }
    else{
        return a1->right-a2->right;
    }
}
long int max=0;
long int n=0;
void find_intervels(long int now,long int count,intervel *last){
    if(now==n){
        if(count>max){
            max=count;
        }
        return;
    }
    if(last==NULL||arr[now].left>=last->right){
        find_intervels(now+1,count+1,&arr[now]);
    }
    find_intervels(now+1,count,last);
}
 int main(){
    scanf("%ld",&n);
    for(int i=0;i<n;i++){
        //arr[i] = (intervel*)malloc(sizeof(intervel));
        scanf("%ld %ld",&arr[i].left,&arr[i].right);
    }
    qsort(arr,n,sizeof(intervel),cmp);

    find_intervels(0,0,NULL);
    printf("%ld",max);
    return 0;
 }
```

下面是贪心算法：

```c
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

```

二者的区别如下：

详细解释一下贪心算法在这个问题中的应用。

### 问题回顾
给定n个开区间(left, right)，要选择尽可能多的区间，使得所选区间互不重叠。

### 贪心策略解释
贪心的核心思想是：**优先选择右端点最小的区间**。

让我们通过一个具体例子来说明：

```
输入：5个区间
(1,4), (2,3), (3,5), (4,6), (1,2)
```

#### 解题步骤：

1. **首先按右端点排序**：
```
排序后：
(1,2)  // 右端点=2
(2,3)  // 右端点=3
(1,4)  // 右端点=4
(3,5)  // 右端点=5
(4,6)  // 右端点=6
```

2. **贪心选择过程**：
- 选择第一个区间(1,2)，因为它的右端点最小
- 当前右端点=2
- 检查下一个区间(2,3)：因为2>=2，可以选择
- 当前右端点=3
- 检查下一个区间(1,4)：因为1<3，不能选择
- 检查下一个区间(3,5)：因为3>=3，可以选择
- 当前右端点=5
- 检查下一个区间(4,6)：因为4<5，不能选择

3. **最终结果**：
选择了3个区间：(1,2), (2,3), (3,5)

### 为什么这样是对的？

贪心策略的正确性基于以下事实：
1. 如果我们要选择尽可能多的不重叠区间，应该让每个选择的区间尽可能"小"
2. 右端点越小，给后面的区间留下的空间就越大
3. 按右端点排序后，每次选择都是局部最优的，最终能达到全局最优

### 代码实现讲解

```c
// 比较函数：按右端点排序
int compareIntervals(const void *p1, const void *p2) {
    Interval *a1 = (Interval*)p1;
    Interval *a2 = (Interval*)p2;
    // 首先按右端点排序
    if (a1->right != a2->right) {
        return a1->right - a2->right;
    }
    // 右端点相同时，按左端点降序排序
    return a2->left - a1->left;
}

// 贪心算法主体
int maxNonOverlappingIntervals(Interval *intervals, long int n) {
    if (n <= 0) return 0;
    
    // 1. 按右端点排序
    qsort(intervals, n, sizeof(Interval), compareIntervals);
    
    int count = 1;  // 至少能选择一个区间
    long int currentEnd = intervals[0].right;  // 记录当前选中区间的右端点
    
    // 2. 遍历所有区间
    for (long int i = 1; i < n; i++) {
        // 3. 如果当前区间的左端点 >= 上一个选中区间的右端点
        if (intervals[i].left >= currentEnd) {
            count++;  // 选择这个区间
            currentEnd = intervals[i].right;  // 更新右端点
        }
    }
    
    return count;
}
```

### 时间复杂度分析
- 排序时间：\(O(n\log n)\)
- 遍历一次：\(O(n)\)
- 总时间复杂度：\(O(n\log n)\)

### 与递归回溯的比较
您原来的递归回溯方法：
- 尝试每个区间的选择和不选择
- 时间复杂度是 \(O(2^n)\)
- 当n很大时会非常慢

而贪心算法：
- 只需要排序后遍历一次
- 时间复杂度是 \(O(n\log n)\)
- 能够高效处理大规模输入

这就是为什么在这类问题中，贪心算法比递归回溯更有效率。

### 关于贪心算法，有一个重要问题——为什么要按照右端点排序？

**==使用贪心是局部最优达到全局最优==**

### 1. 右端点排序 vs 左端点排序

让我们用一个具体例子来说明：
```
给定区间：
(1,4), (2,3), (3,5), (4,6), (1,2)
```

#### 按左端点排序：
```
排序后：
(1,4)  左端点=1
(1,2)  左端点=1
(2,3)  左端点=2
(3,5)  左端点=3
(4,6)  左端点=4

如果按左端点排序，选择第一个(1,4)会导致错误结果，因为：
- 选择(1,4)后，会排除掉(1,2)、(2,3)
- 最终只能选择(1,4)和(4,6)，总共2个区间
```

#### 按右端点排序：
```
排序后：
(1,2)  右端点=2
(2,3)  右端点=3
(1,4)  右端点=4
(3,5)  右端点=5
(4,6)  右端点=6

按右端点排序，可以得到最优解：
- 首先选择(1,2)
- 然后可以选择(2,3)
- 最后可以选择(3,5)
- 总共选择3个区间
```

### 2. 为什么右端点排序更优？

1. **贪心策略的本质**
   - 我们要选择尽可能多的不重叠区间
   - 每次选择都应该给后面的区间留下更多的空间
   - 右端点越小，给后面区间的空间就越大

2. **决策的确定性**
   - 按右端点排序时，选择当前区间后，我们确切知道还剩多少空间
   - 按左端点排序时，我们无法确定应该选择哪个右端点（比如(1,4)还是(1,2)）

3. **最优子结构**
   - 选择右端点最小的区间后，剩余的问题变成了一个规模更小的相同问题
   - 这保证了局部最优可以导致全局最优

### 3. 举例说明错误情况

```
考虑这样的区间序列：
(1,10), (2,3), (3,4), (4,5), (5,6)

按左端点排序：
(1,10)  // 如果选择这个，只能选择1个区间
(2,3)
(3,4)
(4,5)
(5,6)

按右端点排序：
(2,3)   // 选择这个，然后可以选择(3,4),(4,5),(5,6)
(3,4)
(4,5)
(5,6)
(1,10)
```

### 4. 代码中的体现

```c
// 按右端点排序的比较函数
int compareIntervals(const void *p1, const void *p2) {
    Interval *a1 = (Interval*)p1;
    Interval *a2 = (Interval*)p2;
    if (a1->right != a2->right) {
        return a1->right - a2->right;  // 首先按右端点排序
    }
    return a2->left - a1->left;  // 右端点相同时，按左端点降序
}
```

### 5. 总结

1. **最优性保证**
   - 右端点排序确保了每次选择都是最优的
   - 选择右端点最小的区间可以为后续选择留下最大空间

2. **决策的确定性**
   - 右端点排序提供了明确的选择标准
   - 避免了左端点排序可能带来的决策困境

3. **贪心策略的正确性**
   - 右端点排序符合贪心策略的核心思想
   - 保证了局部最优可以达到全局最优

这就是为什么在区间选择问题中，按右端点排序是更优的选择。它能保证算法的正确性，并且能得到最优解。