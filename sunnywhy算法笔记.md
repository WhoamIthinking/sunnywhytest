# sunnywhy算法笔记

**==从现在开始这几道题遇到不会的我就开始写笔记==**

## 125——将一个正整数分解

```c
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
    printf("请输入一个正整数: ");
    scanf("%d", &n); // 输入一个正整数
    if (n <= 1) {
        printf("没有方案\n"); // 如果 n 小于等于 1，则没有有效的分解方案
    } else {
        // 减去1是因为至少要两个正整数之和
        printf("方案数: %d\n", countWays(n, 1) - 1); // 计算并输出分解方案数
    }
    return 0;
}

```

对于上述代码，表面上来说没什么特殊的，关键是注意countways中的另一个参数：min

### 解释 `countWays` 函数中的 `min` 参数

`min` 参数在 `countWays` 函数中起到了限制最小分解数的作用。以下是详细解释：

test_125.c

#### `min` 参数的作用

1. **限制最小分解数**:
   - `min` 参数确保在递归过程中，每次分解时使用的数不会小于上一次分解时使用的数。
   - 例如，如果当前分解数为 `i`，那么下一次递归调用时，最小分解数将是 `i`，即 `countWays(n - i, i)`。
2. **避免重复方案**:
   - 通过限制最小分解数，避免了重复计算相同的分解方案。例如，分解 5 为 2+3 和 3+2 是相同的方案，通过 `min` 参数可以避免这种重复。
3. **递归终止条件**:
   - 当 `n` 为 0 时，表示找到了一种有效的分解方案，返回 1。
   - 递归过程中，`min` 参数逐步增加，确保每次分解时使用的数不会小于上一次，从而保证了方案的唯一性和有效性。

总结来说，`min` 参数在 `countWays` 函数中起到了限制最小分解数和避免重复方案的作用，确保了递归过程中的分解方案是唯一且有效的。

**==同时，要注意这个代码一开始在函数中并没有限制1与0的正整数分解，这是为了减少干扰==**

## 128——01串

需要注意这个问题，卡了我好长时间：

**当我写为x+(1<<(n-1))就可以了，但是当我写为x+1<<(n-1)时在最后一步就不行，这是为啥呢么？**

这是因为运算符的优先级问题。

在表达式 `x + 1 << (n-1)` 中，运算符 `+` 和 `<<` 的优先级不同。具体来说，位移运算符 `<<` 的优先级低于加法运算符 `+`。因此，表达式 `x + 1 << (n-1)` 会被解析为 `(x + 1) << (n-1)`，而不是 `x + (1 << (n-1))`。

### 具体解释

- `x + 1 << (n-1)` 被解析为 `(x + 1) << (n-1)`：
  - 先计算 `x + 1`，得到一个中间结果。
  - 然后对这个中间结果进行左移 `(n-1)` 位。
- `x + (1 << (n-1))`：
  - 先计算 `1 << (n-1)`，得到一个中间结果。
  - 然后将 `x` 加上这个中间结果。

### 示例

假设 `x = 2`，`n = 3`：

- `x + 1 << (n-1)`：
  - 先计算 `x + 1`，即 `2 + 1 = 3`。
  - 然后计算 `3 << 2`，即 `3 * 2^2 = 3 * 4 = 12`。
- `x + (1 << (n-1))`：
  - 先计算 `1 << 2`，即 `1 * 2^2 = 4`。
  - 然后计算 `2 + 4 = 6`。

### 解决方法

为了确保运算顺序正确，你需要使用括号来明确表达式的优先级：

chains(n-1, x + (1 << (n-1)), y+1);

这样可以确保先进行位移操作，然后再进行加法运算。 这样可以确保先进行位移操作，然后再进行加法运算。

## 129——生成子集

```c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int a[5000][12];

void generate(int n){
    int i=0;
    int j;
    for(i=0;i<pow(2,n);i++){
        for(j=0;j<n;j++){
            if(i&(1<<j)){
                a[i][j]=1;
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
        if (arrA[i] == 1) sizeA++;
        if (arrB[i] == 1) sizeB++;
    }

    // 按子集大小排序
    if (sizeA != sizeB) return sizeA - sizeB;

    // 如果大小相同，按字典序排序
    for (int i = 0; i < 12; i++) {
        if (arrA[i] != arrB[i]) return arrA[i] - arrB[i];
    }

    return 0;
}

// 排序函数
void mysort(int n) {
    qsort(a, (int)pow(2, n), sizeof(a[0]), compare);
}

int main(){
    int n;
    scanf("%d",&n);
    int i=0,j=0;
    for(i=0;i<pow(2,n);i++){
        for(j=0;j<n;j++){
            a[i][j]=0;
        }
    }
    generate(n);
    mysort(n);
    for(i=0;i<pow(2,n);i++){
        for(j=0;j<n;j++){
            if(a[i][j]==1){
                printf("%d ",j+1);
            }
        }
        printf("\n");
    }
    return 0;
}
```

本题的解法我参考了人工智能，是一个非常巧妙的解法，因为任意一个长度为n的集合都最多可以分解为pow(2,n)(即2的n次方)个子集。而对n，利用上题中的01串，刚好能化为2的n次方的串，故用此来表示

### 代码功能
这段代码的主要功能是生成一个正整数 `n` 的所有子集，并对这些子集进行排序。排序规则是：
1. 子集的元素个数少的优先。
2. 元素个数相同的子集按字典序排序。

### 代码结构
1. **全局变量**：
   ```c
   int a[5000][12];
   ```
   这是一个二维数组，用于存储所有子集。假设 `n` 的最大值为 12，因此最多有 `2^12 = 4096` 个子集，每个子集最多包含 12 个元素。

2. **生成子集的函数 `generate`**：
   ```c
   void generate(int n) {
       int i = 0;
       int j;
       for (i = 0; i < pow(2, n); i++) {
           for (j = 0; j < n; j++) {
               if (i & (1 << j)) {
                   a[i][j] = 1;
               }
           }
       }
   }
   ```
   这个函数生成所有子集，并将它们存储在全局数组 `a` 中。外层循环遍历所有可能的子集，总共有 `2^n` 个子集。内层循环遍历每个元素，通过位运算 `i & (1 << j)` 检查当前子集是否包含第 `j` 个元素。如果包含，则将 `a[i][j]` 设置为 1。

   **举例说明**：
   假设 `n = 3`，则有 `2^3 = 8` 个子集。对于每个 `i`，内层循环检查每个元素是否在子集中：
   - `i = 0`：子集为空集 `{}`
   - `i = 1`：子集为 `{1}`
   - `i = 2`：子集为 `{2}`
   - `i = 3`：子集为 `{1, 2}`
   - `i = 4`：子集为 `{3}`
   - `i = 5`：子集为 `{1, 3}`
   - `i = 6`：子集为 `{2, 3}`
   - `i = 7`：子集为 `{1, 2, 3}`

3. **比较函数 `compare`**：
   ```c
   int compare(const void *p1, const void *p2) {
       int *arrA = (int *)p1;
       int *arrB = (int *)p2;
       int sizeA = 0, sizeB = 0;
   
       // 计算子集的大小
       for (int i = 0; i < 12; i++) {
           if (arrA[i] == 1) sizeA++;
           if (arrB[i] == 1) sizeB++;
       }
   
       // 按子集大小排序
       if (sizeA != sizeB) return sizeA - sizeB;
   
       // 如果大小相同，按字典序排序
       for (int i = 0; i < 12; i++) {
           if (arrA[i] != arrB[i]) return arrB[i] - arrA[i];
       }
   
       return 0;
   }
   ```
   这个函数用于 `qsort` 函数的比较器，按照子集大小和字典序排序。首先计算两个子集的大小，然后按大小排序。如果大小相同，则按字典序排序。

   ==`qsort(a, (int)pow(2, n), sizeof(a[0]), compare);` 这个函数的作用是对数组 `a` 进行排序。==具体来说：
   
   - `a` 是要排序的数组。
   - `(int)pow(2, n)` 是数组 `a` 中元素的数量，即子集的总数。
   - `sizeof(a[0])` 是数组 `a` 中每个元素的大小。
   - `compare` 是一个比较函数，用于确定两个元素的顺序。
   
   `qsort` 函数会根据 `compare` 函数的结果对数组 `a` 进行排序，使得子集按照指定的顺序排列。
   
   
   
   **同时要明白`qsort` 函数可以对二维数组进行排序，因为二维数组实际上是一个指针数组。`qsort` 函数通过比较函数 `compare` 来确定两个元素的顺序。具体来说，`qsort` 会将数组中的每一行视为一个元素，并使用 `compare` 函数来比较这些行。**
   
   
   
   **`sizeof(a[0])` 是数组 `a` 中每一行的大小，因为 `a` 是一个二维数组，`a[0]` 表示数组 `a` 的第一行。对于二维数组 `int a[5000][12]`，`a[0]` 是一个包含 12 个 `int` 元素的一维数组。因此，`sizeof(a[0])` 返回的是这个一维数组的大小，即 12 个 `int` 元素的大小。**
   
   **具体来说，`sizeof(a[0])` 等于 `12 * sizeof(int)`，表示数组 `a` 中每一行的大小。**
   
   
   
4. **主函数 `main`**：
   
   ```c
   int main() {
       int n;
       scanf("%d", &n);
       int i = 0, j = 0;
       for (i = 0; i < pow(2, n); i++) {
           for (j = 0; j < n; j++) {
               a[i][j] = 0;
           }
       }
       generate(n);
       mysort(n);
       for (i = 0; i < pow(2, n); i++) {
           for (j = 0; j < n; j++) {
               if (a[i][j] == 1) {
                   printf("%d ", j + 1);
               }
           }
           printf("\n");
       }
       return 0;
   }
   ```
   主函数读取输入的整数 `n`，初始化数组 `a`，调用 `generate` 函数生成所有子集，调用 `mysort` 函数对子集进行排序，最后打印所有子集。

### 举例说明
假设输入 `n = 3`，则生成的子集和排序结果如下：
- 生成的子集：
  ```
  {}
  {1}
  {2}
  {1, 2}
  {3}
  {1, 3}
  {2, 3}
  {1, 2, 3}
  ```
- 排序后的子集：
  ```
  {}
  {1}
  {2}
  {3}
  {1, 2}
  {1, 3}
  {2, 3}
  {1, 2, 3}。
  ```

最后还要考虑行末不能有空格，可以做如下修改：

```c
  for(i=0;i<pow(2,n);i++){
        int first = 1; // 标记是否是第一个元素
        for(j=0;j<n;j++){
            if(a[i][j]==1){
                if (!first) {
                    printf(" ");
                }
                printf("%d", j+1);
                first = 0;
            }
        }
        printf("\n");
    }
```

==**使用first标记用于判断是不是第一个元素**==

## 130——分解子集2

是在上题基础上增加了自己定义各个集合中的元素，故而只需在原来的`a[i][j]`处由原来的1变为自己规定的数字即可，代码如下：

```c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int a[5000][12];
void generate(int n,int b[]){
    int i=0;
    int j;
    for(i=0;i<pow(2,n);i++){
        for(j=0;j<n;j++){
            if(i&(1<<j)){
                a[i][j]=b[j];
                //printf("%d\n",a[i][j]);
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
        if (arrA[i] !=0) sizeA++;
        if (arrB[i] !=0) sizeB++;
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

int main(){
    int n;
    scanf("%d",&n);
    int i=0,j=0;
    for(i=0;i<pow(2,n);i++){
        for(j=0;j<n;j++){
            a[i][j]=0;
        }
    }
    int *b=(int *)malloc(sizeof(int)*n);
    for(j=0;j<n;j++){
        scanf("%d",&b[j]);
    }
    generate(n,b);
    mysort(n);
    for(i=0;i<pow(2,n);i++){
        int first = 1; // 标记是否是第一个元素
        for(j=0;j<n;j++){
            if(a[i][j]!=0){
                if (!first) {
                    printf(" ");
                }
                printf("%d", a[i][j]);
                first = 0;
            }
        }
        printf("\n");
    }
    return 0;
}
```

## 131——子集3

主要还是在子集二的基础上，只是再次升级，当输入的元素有重复时可以去重，但是不知道为什么在网上与我本地跑的不一样

```C
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

```

## 132——全排列1

对于分解子集来说可以使用01串来取巧，但是对于全排列，只能使用递归来算，其代码如下：

```c
#include <stdio.h>
#include <stdlib.h>
int a[45000][8];
int k=0;
// 迭代计算阶乘的函数
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
int compare(const void *p1,const void *p2){
    int *arra=(int*)p1;
    int* arrb=(int*)p2;
    int anum=0,bnum=0;
    for(int i=0;i<8;i++){
        if(arra[i]!=0) anum++;
        if(arrb[i]!=0) bnum++;
    }
    if(anum!=bnum) return anum-bnum;
    for(int i=0;i<8;i++){
        if(arra[i]!=arrb[i]) return arra[i]-arrb[i];
    }
    return 0;
}

void mysort(int n){
    qsort(a,(int)factorial(n),sizeof(a[0]),compare);
}

void printmute(int n){
    for(int i=0;i<(int)factorial(n);i++){
        for(int j=0;j<n;j++){
            if(j>0) printf(" ");
            printf("%d",a[i][j]);
        }
        printf("\n");
    }
}

void permute(int* arr,int start,int end){
    if(start==end){
        for(int i=0;i<=end;i++){
            a[k][i]=arr[i];
        }
        k++;
    }
    else{
        for(int i=start;i<=end;i++){
            swap(&arr[start],&arr[i]);
            permute(arr,start+1,end);
            swap(&arr[start],&arr[i]);
        }
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int *arr=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<(int)factorial(n);i++){
        for(int j=0;j<n;j++){
            a[i][j]=0;
        }
    }
    for(int i=0;i<n;i++){
        arr[i]=i+1;
    }
    permute(arr,0,n-1);
    mysort(n);
    printmute(n);
    return 0;
}
```

在此代码中最为关键的就是permute计算全排列，其中关于此代码的具体解释如下：

### 函数定义
```c
void permute(int *arr, int start, int end) {
```
这个函数用于生成数组 `arr` 的全排列。`start` 和 `end` 分别表示当前排列的起始和结束索引。

### 基本情况
```c
if (start == end) {
    // 打印当前排列
    for (int i = 0; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
```
当 `start` 等于 `end` 时，表示已经生成了一个完整的排列，此时打印当前排列。

### 递归生成排列
```c
else {
    for (int i = start; i <= end; i++) {
        // 交换元素
        swap(&arr[start], &arr[i]);
        // 递归生成剩余元素的排列
        permute(arr, start + 1, end);
        // 还原交换
        swap(&arr[start], &arr[i]);
    }
}
```
否则，通过交换 `start` 和 `i` 位置的元素，递归生成剩余元素的排列，然后还原交换。

### 详细解释和举例

假设我们有一个数组 `arr = {1, 2, 3}`，我们调用 `permute(arr, 0, 2)` 来生成其全排列。

1. **初始调用**：
   ```c
   permute(arr, 0, 2);
   ```
   `start = 0`，`end = 2`，进入 `else` 分支。

2. **第一次循环**：
   ```c
   for (int i = 0; i <= 2; i++) {
       swap(&arr[0], &arr[i]);
       permute(arr, 1, 2);
       swap(&arr[0], &arr[i]);
   }
   ```
   - 当 `i = 0` 时，`swap(&arr[0], &arr[0])` 不改变数组，递归调用 `permute(arr, 1, 2)`。

3. **递归调用**：
   ```c
   permute(arr, 1, 2);
   ```
   `start = 1`，`end = 2`，进入 `else` 分支。

4. **第二次循环**：
   ```c
   for (int i = 1; i <= 2; i++) {
       swap(&arr[1], &arr[i]);
       permute(arr, 2, 2);
       swap(&arr[1], &arr[i]);
   }
   ```
   - 当 `i = 1` 时，`swap(&arr[1], &arr[1])` 不改变数组，递归调用 `permute(arr, 2, 2)`。

5. **打印排列**：
   ```c
   permute(arr, 2, 2);
   ```
   `start = 2`，`end = 2`，进入 `if` 分支，打印当前排列 `1 2 3`。

6. **还原交换**：
   ```c
   swap(&arr[1], &arr[1]);
   ```
   还原交换，不改变数组。

7. **继续循环**：
   - 当 `i = 2` 时，`swap(&arr[1], &arr[2])` 交换元素，数组变为 `1 3 2`，递归调用 `permute(arr, 2, 2)`。

8. **打印排列**：
   ```c
   permute(arr, 2, 2);
   ```
   `start = 2`，`end = 2`，进入 `if` 分支，打印当前排列 `1 3 2`。

9. **还原交换**：
   ```c
   swap(&arr[1], &arr[2]);
   ```
   还原交换，数组变回 `1 2 3`。

10. **继续外层循环**：
    - 当 `i = 1` 时，`swap(&arr[0], &arr[1])` 交换元素，数组变为 `2 1 3`，递归调用 `permute(arr, 1, 2)`。

11. **重复上述步骤**：
    继续递归调用和交换，生成并打印所有排列。

### 总结
通过递归和交换，`permute` 函数生成了数组的所有排列。每次递归调用处理一个元素的位置，通过交换和还原交换，确保生成所有可能的排列组合。

而对于其中需要注意的点还有就是swap函数：

```c
void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
```

用于交换指针的地址而非指针
