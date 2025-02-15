# sunnywhy算法笔记（152-）

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

## 153——使用贪心算法求解闭区间点

此题的算法如下：

```c
#include<stdio.h>
#include<stdlib.h>
typedef struct interval{
    long int left;
    long int right;
}interval;
int cmp(const void *p1,const void *p2){
    interval *a1=(interval*)p1;
    interval *a2=(interval*)p2;
    if(a1->right!=a2->right){
        return a1->right-a2->right;
    }
    return a2->left-a1->left;
}
interval a[15000];
int find_points(long int n){
    qsort(a,n,sizeof(interval),cmp);
    int count=1;
    //long int front=a[0].left;
    long int end=a[0].right;
    for(int i=1;i<n;i++){
        if(end<a[i].left){
            count++;
            end=a[i].right;
        }
    }
    return count;
}
int main(){
    long int n;
    scanf("%ld",&n);
    for(int i=0;i<n;i++){
        scanf("%ld %ld",&a[i].left,&a[i].right);
    }
    int t=find_points(n);
    printf("%d",t);
    return 0;
}
```

对于这个题，同样是使用贪心算法的一个例子，但是此题相较于上一道题有以下需要明白的问题：

### 为何cmp函数当右端点相同时需要按照左端点降序排序？

这是一个很好的问题。在右端点相同时，按左端点降序排序是一个优化处理，让我解释一下原因：

### 1. 为什么需要处理右端点相同的情况？

考虑这样的例子：
```
(1,3), (2,3)
```
这两个区间右端点都是3，如果不对左端点进行特殊处理，可能会出现任意顺序。

### 2. 为什么选择降序而不是升序？

考虑这个例子：
```
(1,3), (2,3)
```

#### 如果按左端点升序排列：
```
(1,3)  // 左端点=1
(2,3)  // 左端点=2
```

#### 如果按左端点降序排列：
```
(2,3)  // 左端点=2
(1,3)  // 左端点=1
```

选择降序更优，因为：

1. **包含关系处理**
   - 当右端点相同时，左端点小的区间一定包含了左端点大的区间
   - (1,3)完全包含了(2,3)
   - 选择(2,3)比选择(1,3)更优，因为它是更"小"的区间

2. **贪心策略的延续**
   - 在右端点相同的情况下，选择左端点大的区间可以减少对其他区间的影响
   - 这符合贪心的思想：每次选择影响范围最小的解

3. **避免冗余**
   - 如果有(1,3)和(2,3)，选择(2,3)已经足够覆盖需求
   - 不需要选择范围更大的(1,3)

### 3. 具体示例

```
考虑这样的区间序列：
(1,3), (2,3), (1,2)

按右端点排序，同右端点按左端点降序：
(1,2)
(2,3)  // 2比1大，所以(2,3)在(1,3)前面
(1,3)
```

这样排序后：
- 首先选择(1,2)
- 然后在右端点为3的区间中，优先考虑(2,3)而不是(1,3)
- 这样的选择更有利于得到最优解

### 4. 代码分析

```c
if (a1->right != a2->right) {
    return a1->right - a2->right;  // 首先按右端点排序
}
return a2->left - a1->left;  // 右端点相同时，按左端点降序
```

- 第一个条件确保按右端点升序排序
- 当右端点相同时，使用a2->left - a1->left实现左端点降序
  - 如果a2的左端点大于a1的左端点，返回正数，a2排在前面
  - 如果a2的左端点小于a1的左端点，返回负数，a1排在前面

### 5. 总结

1. **优化效果**
   - 这种排序方式可以在右端点相同时选择更优的区间
   - 避免了不必要的区间选择

2. **贪心策略的完整性**
   - 补充了右端点相同情况下的决策规则
   - 保持了贪心策略的一致性

3. **实现的简洁性**
   - 通过简单的比较函数实现了复杂的排序逻辑
   - 使得整体算法更加高效和优雅

这种排序方式是对基本贪心策略的优化，使得算法在处理特殊情况时也能保持最优性。

### 为什么第一个点放在第一个区间的右端点

让我解释为什么要把第一个点放在第一个区间的右端点：

### 1. 贪心策略的核心思想

在区间覆盖问题中，我们的目标是用最少的点覆盖所有区间。放置点的位置应该满足两个条件：
1. 能覆盖当前区间
2. 尽可能覆盖更多的后续区间

### 2. 为什么选择右端点？

考虑第一个区间(L1, R1)，我们有三种可能的选择：

1. **选择左端点L1**
```
[L1]----R1
    |-------|  // 后续区间
```
- 问题：无法最大化覆盖后续区间
- 浪费了可能覆盖更多区间的机会

2. **选择中间某点M**
```
L1----[M]----R1
    |-------|  // 后续区间
```
- 问题：比右端点覆盖的区间更少
- 没有任何优势

3. **选择右端点R1**
```
L1----[R1]
    |-------|  // 后续区间
```
- 优势：能覆盖最多的后续区间
- 这是最优选择

### 3. 具体例子说明

考虑这样的区间序列：
```
(1,3), (2,4), (2,3), (3,5)
```

#### 如果选择左端点(x=1)：
```
[1]--3
  2--4
  2--3
    3--5

结果：需要3个点(1,3,5)才能覆盖所有区间
```

#### 如果选择右端点(x=3)：
```
1--[3]
2--4
2--3
3--5

结果：只需要2个点(3,5)就能覆盖所有区间
```

### 4. 正确性证明

1. **最优性证明**
   - 假设存在比右端点更优的选择P
   - P一定在区间内：L1 ≤ P ≤ R1
   - 任何P < R1的点能覆盖的区间，R1都能覆盖
   - 因此R1至少不比P差

2. **反证法**
   - 假设不选择右端点是最优的
   - 那么选择的点P必然在R1左边
   - 这意味着可能会错过一些只能被R1覆盖的区间
   - 与最优解假设矛盾

### 5. 算法实现的体现

```c
int minPoints(Interval *intervals, int n) {
    if (n <= 0) return 0;
    
    // 按右端点排序
    qsort(intervals, n, sizeof(Interval), compareIntervals);
    
    // 第一个点放在第一个区间的右端点
    int current_point = intervals[0].right;
    int count = 1;
    
    for (int i = 1; i < n; i++) {
        if (intervals[i].left > current_point) {
            current_point = intervals[i].right;
            count++;
        }
    }
    
    return count;
}
```

### 6. 总结

1. **贪心策略的正确性**
   - 选择右端点是局部最优解
   - 这个局部最优解导致全局最优解

2. **实现的简洁性**
   - 通过选择右端点简化了算法逻辑
   - 不需要考虑其他复杂的选点策略

3. **效率保证**
   - 右端点选择确保了使用最少的点
   - 避免了不必要的点的添加

因此，选择第一个区间的右端点作为第一个点是这个贪心算法的关键，它保证了算法能够得到最优解。



## 177——双指针实现归并排序

**==之前几天都没有写总结这就导致一个问题——之前的代码再反过来复习就完全忘记了，不知道当时在写这个代码是遇到了什么问题==**因此以后一定要写一道总结一道

对于本题代码如下：

```c
#include<stdio.h>
#include<stdlib.h>
int* merge(int *p1,int *p2,int m,int n){
    int *p=(int*)malloc(sizeof(int )*(m+n));
    int i=0,j=0,k=0;
    while(i<m&&j<n){
        if(p1[i]<=p2[j]){
            p[k]=p1[i];
            i++;
            k++;
        }
        else{
            p[k]=p2[j];
            j++;
            k++;
        }
    }
    while(i<m){
        p[k]=p1[i];
        i++;
        k++;
    }
    while(j<n){
        p[k]=p2[j];
        k++;
        j++;
    }
    return p;
}
int*  merge_sort(int *p,int left,int right){
    if (left == right) {
        int* t=(int*)malloc(sizeof(int));
        t[0]=p[left];
        return t;
    }
    if(left==right-1){
        int*t=merge(&p[left],&p[right],1,1);
        return t;
    }
    int mid=(left+right)/2;
    int *p1=merge_sort(p,left,mid);
    int *p2=merge_sort(p,mid+1,right);
    int *t=merge(p1,p2,mid-left+1,right-mid);
    free(p1);
    free(p2);
    return t;
}
int main(){
    int n;
    scanf("%d",&n);
    int* p=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&p[i]);
    }
    p=merge_sort(p,0,n-1);
    for(int i=0;i<n;i++){
        if(i>0){
            printf(" ");
        }
        printf("%d",p[i]);
    }
    free(p);
    return 0;
}
```

其中关键问题在于

```c
if (left == right) {
        int* t=(int*)malloc(sizeof(int));
        t[0]=p[left];
        return t;
    }
```

此处条件变量设置，我之前直接做的是`return p`即直接返回p数组，比如：

- 在 `merge_sort(p, 2, 2)` 中：
  - `left = 2`, `right = 2`
  - 进入 `if (left == right)` 分支，返回了整个数组 `p`，而不是一个包含单个元素的数组。

## 178——双指针实现快速排序

此题代码如下：

```c
#include<stdio.h>
#include<stdlib.h>
void quick_sort_num(int p[],int begin,int end){
    if(begin>=end){
        return;
    }
    int mid=(begin+end)>>1;
    int temp=p[begin];
    p[begin]=p[mid];
    p[mid]=temp;
    int mark=p[begin];
    int i=begin;
    int j=end;
    while(i<j){
        while(i < j && p[j] >= mark) j--;
        p[i] = p[j];
        while(i < j && p[i] <= mark) i++;
        p[j] = p[i];
    }
    p[i]=mark;
    //return p;
    quick_sort_num(p,begin,i-1);
    quick_sort_num(p,i+1,end);
}
int main(){
    int n;
    scanf("%d",&n);
    int *a=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    quick_sort_num(a,0,n-1);
    for(int i=0;i<n;i++){
        if(i>0){
            printf(" ");
        }
        printf("%d",a[i]);
    }
    free(a);
    return 0;
}
```

对于此题我犯了一个很大的错误，一开始我将begin作为枢纽来进行比较，然而发生了超时，我找了很长时间都没有刚发现问题在哪，直到人工智能提醒了我，主要发生在如下片段：

```c
while(i<j){
        while(i < j && p[j] >= mark) j--;
        p[i] = p[j];
        while(i < j && p[i] <= mark) i++;
        p[j] = p[i];
    }
    p[i]=mark;
    //return p;
    quick_sort_num(p,begin,i-1);
    quick_sort_num(p,i+1,end);
```

我原来使用的是>而非>=这就导致会进行很多重复运算从而造成超时

## 186——使用前缀和计算012对

本题的解法代码如下所示：

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int64_t count0 = 0, count1 = 0, count2 = 0;
    int64_t result = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            count0++;
        } else if (arr[i] == 1) {
            count1 += count0;
        } else if (arr[i] == 2) {
            result += count1;
        }
    }
    
    printf("%lld\n", result);
    
    free(arr);
    return 0;
}
```

### 本题主要是要理解前缀和的思想：

这段代码使用了一种称为“前缀和”的思想来高效地计算序列中的012对。让我们详细解释其中的思想，并通过一个具体的例子来说明为什么这样做。

### 思想解释

1. **前缀和思想**：
   - 前缀和是一种通过累积前面的元素来简化计算的方法。
   - 在这个问题中，我们通过累积0和1的数量来计算012对。

2. **计数器的作用**：
   - `count0`：记录到目前为止出现的0的数量。
   - `count1`：记录到目前为止可以形成的01对的数量。
   - `result`：记录到目前为止可以形成的012对的数量。

### 代码解释

```c
for (int i = 0; i < n; i++) {
    if (arr[i] == 0) {
        count0++;
    } else if (arr[i] == 1) {
        count1 += count0;
    } else if (arr[i] == 2) {
        result += count1;
    }
}
```

- 遍历数组中的每一个元素：
  - 如果元素是0，增加 `count0` 的数量。
  - 如果元素是1，增加 `count1` 的数量，增加的量是当前 `count0` 的数量，因为每一个0都可以和这个1形成一个01对。
  - 如果元素是2，增加 `result` 的数量，增加的量是当前 `count1` 的数量，因为每一个01对都可以和这个2形成一个012对。

### 举例说明

假设输入如下：
```
6
0 1 0 2 1 2
```

#### 详细步骤

1. **初始化**：
   - `count0 = 0`
   - `count1 = 0`
   - `result = 0`

2. **遍历数组**：
   - 第1个元素是 `0`：
     - `count0++`，所以 `count0 = 1`
   - 第2个元素是 `1`：
     - `count1 += count0`，所以 `count1 = 1`
   - 第3个元素是 `0`：
     - `count0++`，所以 `count0 = 2`
   - 第4个元素是 `2`：
     - `result += count1`，所以 `result = 1`
   - 第5个元素是 `1`：
     - `count1 += count0`，所以 `count1 = 3`
   - 第6个元素是 `2`：
     - `result += count1`，所以 `result = 4`

### 解释

- 第1个 `0` 和第2个 `1` 以及第4个 `2` 形成一个012对
- 第1个 `0` 和第5个 `1` 以及第4个 `2` 形成一个012对
- 第3个 `0` 和第2个 `1` 以及第4个 `2` 形成一个012对
- 第3个 `0` 和第5个 `1` 以及第6个 `2` 形成一个012对

总共有4个012对。

### 总结

通过这种方法，我们可以高效地计算序列中的012对。前缀和思想使得我们能够在一次遍历中完成计算，而不需要进行多次嵌套遍历，从而提高了算法的效率。如果有任何问题，请随时提问。

## 189——使用最小堆查找第k小的元素

对于本题我一开始时使用遍历查找最小值，每找到一个最小值就把这个变为99999，只要找k次就可以，但是这样做会超时，因此需要降低时间复杂度，故而需要使用堆来降低，

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct HEAP {
    int *data;
    int size;
} heap;

heap* heap_create(int n) {
    heap *h = (heap*)malloc(sizeof(heap));
    h->data = (int *)malloc(sizeof(int) * (n + 1));
    h->size = 0;
    return h;
}

void heap_sift_up(heap *h, int idx) {
    while (idx > 1 && h->data[idx] < h->data[idx / 2]) {
        int temp = h->data[idx];
        h->data[idx] = h->data[idx / 2];
        h->data[idx / 2] = temp;
        idx /= 2;
    }
}

void heap_sift_down(heap *h, int idx) {
    while (2 * idx <= h->size) {
        int j = 2 * idx;
        if (j < h->size && h->data[j] > h->data[j + 1]) {
            j++;
        }
        if (h->data[idx] <= h->data[j]) {
            break;
        }
        int temp = h->data[idx];
        h->data[idx] = h->data[j];
        h->data[j] = temp;
        idx = j;
    }
}

void heap_insert(heap *h, int value) {
    h->data[++h->size] = value;
    heap_sift_up(h, h->size);
}

int heap_delete_min(heap *h) {
    int min_value = h->data[1];
    h->data[1] = h->data[h->size--];
    heap_sift_down(h, 1);
    return min_value;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    heap *h = heap_create(n);
    for (int i = 0; i < n; i++) {
        heap_insert(h, a[i]);
    }

    for (int i = 0; i < k - 1; i++) {
        heap_delete_min(h);
    }

    int p = heap_delete_min(h);
    printf("%d\n", p);

    free(a);
    free(h->data);
    free(h);
    return 0;
}
```

如上需要注意实际运用与王道书理论中的差别，实际运用应当使用上过滤与下过滤而不应当是直接使用对调整算法，原因如下：

### 详细解释上滤（sift-up）和下滤（sift-down）操作与你的调整操作（`heap_modify`）的区别，并通过具体的例子说明。

### 上滤（sift-up）操作

上滤操作用于在插入元素后维护堆的性质。它的基本思想是将新插入的元素与其父节点比较，如果新元素小于父节点，则交换它们的位置，直到堆的性质得到满足。

### 下滤（sift-down）操作

下滤操作用于在删除元素后维护堆的性质。它的基本思想是将堆顶元素与其子节点比较，如果堆顶元素大于子节点，则交换它们的位置，直到堆的性质得到满足。

### 你的调整操作（heap_modify）

你的调整操作在每次插入和删除后都重新调整整个堆。这种方法的时间复杂度为 O(n)，因为它需要遍历整个堆。

### 具体例子说明

假设我们有一个初始堆 `[0, 1, 3, 5, 7, 9, 2, 6]`，其中第一个元素 `0` 是占位符，不参与堆的操作。

#### 插入操作

假设我们要插入元素 `4`。

1. **上滤操作**：
   - 插入 `4` 到堆的末尾，堆变为 `[0, 1, 3, 5, 7, 9, 2, 6, 4]`。
   - 比较 `4` 和其父节点 `5`，因为 `4 < 5`，交换它们的位置，堆变为 `[0, 1, 3, 4, 7, 9, 2, 6, 5]`。
   - 比较 `4` 和其父节点 `3`，因为 `4 >= 3`，停止上滤操作。
2. **你的调整操作**：
   - 重新调整整个堆，从中间节点开始，逐个比较并交换，直到堆的性质得到满足。

#### 删除操作

假设我们要删除堆顶元素 `1`。

1. **下滤操作**：
   - 将堆顶元素 `1` 与堆的最后一个元素 `5` 交换，堆变为 `[0, 5, 3, 4, 7, 9, 2, 6]`。
   - 比较 `5` 和其子节点 `3` 和 `4`，选择较小的 `3`，因为 `5 > 3`，交换它们的位置，堆变为 `[0, 3, 5, 4, 7, 9, 2, 6]`。
   - 比较 `5` 和其子节点 `2` 和 `6`，选择较小的 `2`，因为 `5 > 2`，交换它们的位置，堆变为 `[0, 3, 2, 4, 7, 9, 5, 6]`。
   - 比较 `5` 和其子节点 `6`，因为 `5 <= 6`，停止下滤操作。
2. **你的调整操作**：
   - 重新调整整个堆，从中间节点开始，逐个比较并交换，直到堆的性质得到满足。



## 338——确定树中两个节点的最近公共祖先

解法如下：

```c
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构体
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
 * createTree 函数：
 *   按照先序遍历的顺序创建二叉树，输入中-1表示空结点。
 *   例如输入：3 5 6 -1 -1 2 7 -1 -1 4 -1 -1 表示如下二叉树：
 *
 *           3
 *          / \
 *         5   2
 *        / \  / \
 *       6  7 4 ...
 *
 *   注意：输入格式由用户决定，必须保证输入正确。
 */
TreeNode* createTree() {
    int val;
    if (scanf("%d", &val) != 1) {
        return NULL;
    }
    if (val == -1) {
        return NULL;
    }
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = createTree();
    node->right = createTree();
    return node;
}

/*
 * lowestCommonAncestor 函数：
 *   递归查找二叉树中两个节点的最近公共祖先。
 *   算法思想：
 *     1. 如果当前结点为空，返回 NULL；
 *     2. 如果当前结点等于 p 或 q，则返回当前结点；
 *     3. 递归在左子树和右子树查找；
 *     4. 如果左右子树都返回非 NULL，则当前结点即为 LCA；
 *     5. 否则返回不为 NULL 的那一边。
 */
TreeNode* lowestCommonAncestor(TreeNode* root, int p, int q) {
    if (root == NULL) {
        return NULL;
    }
    if (root->val == p || root->val == q) {
        return root;
    }
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left != NULL && right != NULL) {
        return root;
    }
    return (left != NULL) ? left : right;
}

/*
 * freeTree 函数：
 *   释放二叉树占用的内存。
 */
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    /*
     * 输入说明：
     *   1. 首先按先序遍历顺序输入二叉树数据，其中 -1 表示空结点
     *   2. 输入完树的所有结点后，再输入两个整数，分别表示需要查找最近公共祖先的两个节点的值
     *
     * 例如输入：
     *   3 5 6 -1 -1 2 7 -1 -1 4 -1 -1
     *   5 4
     *
     * 表示构造的树为：
     *
     *         3
     *        / \
     *       5   2
     *      / \
     *     6   7
     *          \
     *           4
     *
     * 查找节点 5 和节点 4 的最近公共祖先。
     */
    TreeNode* root = createTree();
    int p, q;
    scanf("%d %d", &p, &q);
    TreeNode* ancestor = lowestCommonAncestor(root, p, q);
    if (ancestor != NULL) {
        printf("Lowest Common Ancestor: %d\n", ancestor->val);
    } else {
        printf("Lowest Common Ancestor not found.\n");
    }
    freeTree(root);
    return 0;
}
```

下面我们用一个具体例子来解释 lowestCommonAncestor 函数的工作原理。假设有如下二叉树（数字表示结点的值）：

```
        3
       / \
      5   2
     / \
    6   7
         \
          4
```

假设我们要求 5 和 4 的最近公共祖先。下面逐步说明函数如何找到答案：

1. 从根结点开始调用  
   调用 lowestCommonAncestor(root=3, p=5, q=4)  
   - 检查：3 不是目标值 5 也不是 4，所以不直接返回。
   - 递归进入左子树和右子树分别查找。

2. 查找左子树  
   调用 lowestCommonAncestor(root=5, p=5, q=4)  
   - 检查：当前结点 5 正好等于目标 p（5）；此时函数会返回结点 5。  
   - 这样，左子树返回的结果就是结点 5。

3. 查找右子树  
   调用 lowestCommonAncestor(root=2, p=5, q=4)  
   - 检查：2 既不等于 5 也不等于 4。
   - 对节点 2 的左子树和右子树递归查找，但假设节点 2 没有目标结点（或其子树中都找不到 5 或 4），最终会返回 NULL。  
   - 右子树返回的结果为 NULL。

4. 返回结果  
   回到第一次调用（根为 3）：  
   - 左侧返回结点 5，右侧返回 NULL。  
   - 按照算法，如果只有一侧返回非 NULL，则表示“目标结点都在这一侧”，因此最终返回左侧结果，即结点 5。

这样，我们得到结论：5 是 5 和 4 的最近公共祖先。

---

### 代码逻辑解释

函数 lowestCommonAncestor 的代码逻辑如下：

- **终止条件：**

  ```c
  if(root == NULL) return NULL;
  if(root->val == p || root->val == q) return root;
  ```
  
  当到达空结点时返回 NULL；如果当前结点就是目标之一（p 或 q），直接返回当前结点。

- **递归调用：**

  ```c
  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);
  ```

  分别在左右子树中查找两个目标结点。如果在左子树找到了一个目标结点（或者它的最近公共祖先），left 保存该结点；同理右子树返回的结果保存在 right 中。

- **后续判断：**

  ```c
  if (left != NULL && right != NULL)
      return root;
  return (left != NULL) ? left : right;
  ```

  - 如果 left 和 right 都不为空，表示 p 和 q 分别位于左右两侧，因此当前结点 root 就是它们的最近公共祖先。
  - 如果只有一侧（left 或 right）不为空，则说明 p 和 q 都在同一侧，返回不为 NULL 的那一侧。

---

### 示例回顾

在我们的例子中：

- 在根（3）的左子树中，递归返回了结点 5（因为遇到了 p=5）。
- 在根（3）的右子树中，没有找到任何目标结点，所以返回 NULL。
- 最后在根（3）处判断：只有一侧有返回值（结点 5），因此最终结果返回结点 5。

这种递归方法能正确捕捉到两个目标结点出现的位置，通过逐层返回来确定最近公共祖先的位置。希望这个详细的解释能够帮助你理解该函数的工作原理。

