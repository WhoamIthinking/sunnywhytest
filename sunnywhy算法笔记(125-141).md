# sunnywhy算法笔记（125-141）

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



### 对于swap函数的详细解释

而对于其中需要注意的点还有就是swap函数：

```c
void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
```

用于交换指针的地址而非指针，这是因为在 C 语言中，函数参数是按值传递的，这意味着当你将变量传递给函数时，函数接收到的是这些变量的副本，而不是变量本身。因此，如果你直接传递 `x` 和 `y`，`swap` 函数只能交换它们的副本，而不会影响原始变量的值。

为了让 `swap` 函数能够交换原始变量的值，我们需要传递变量的地址（即指针）。通过传递指针，`swap` 函数可以直接访问和修改原始变量的值。

#### 按值传递

如果你直接传递 `x` 和 `y`，函数接收到的是它们的副本：

```c
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 5;
    int y = 10;
    swap(x, y);
    // x 和 y 的值不会改变
    return 0;
}
```

在这种情况下，`swap` 函数只能交换 `a` 和 `b` 的值，而不会影响 `x` 和 `y` 的值。

#### 传递指针

通过传递指针，`swap` 函数可以直接访问和修改原始变量的值：

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5;
    int y = 10;
    swap(&x, &y);
    // x 和 y 的值将被交换
    return 0;
}
```

在这种情况下，`swap` 函数接收到的是 `x` 和 `y` 的地址（即指针），通过解引用指针（`*a` 和 `*b`），`swap` 函数可以直接访问和修改 `x` 和 `y` 的值。

## 133&134——全排列2,3

全排列二就是类似于之前的寻找子集2，在原来的基础上增加了自行输入数字，而全排列3就是又在2的基础上增加了去除重复数字的功能，由于在之前的全排列1我就做了模块化的冗余，因此修改较为简单，最后的代码如下：

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
        if(i!=0&&compare(a[i-1],a[i])==0){
            continue;
        }
        else{
            for(int j=0;j<n;j++){
                if(j>0) printf(" ");
                printf("%d",a[i][j]);
            }
            printf("\n");
        }
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
        scanf("%d",&arr[i]);
    }
    permute(arr,0,n-1);
    mysort(n);
    printmute(n);
    return 0;
}
```

## 135&136&137——组合

对于组合，同样有三组操作，此处直接合到一起以最终版来论述：

```c
#include<stdio.h>
#include<stdlib.h>

int result[3000][12];
int k;
// 阶乘函数
long long factorial(int num) {
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}
// 组合数函数
long long combination(int n, int m) {
    if (m > n) return 0; // 当 m > n 时，组合数为 0
    return factorial(n) / (factorial(m) * factorial(n - m));
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

void mysort(int n,int m){
    qsort(result,(int)combination(n,m),sizeof(result[0]),compare);
}

void generate_combination(int *arr,int n,int m,int index,int *combo,int i,int d){
    if(index==d){
        for(int i=0;i<index;i++){
            result[k][i]=combo[i];
            //printf("$$$%d$$$ &&&&%d&&&&\n",k,i);
        }
        k++;
    }
    else{   
            //printf("combo:$$$%d$$$ &&&&%d&&&&\n",combo[index],index);
            if(n-i<m-index) return;
            combo[index]=arr[i];
            generate_combination(arr,n-1,m-1,index+1,combo,i+1,d);
            generate_combination(arr,n,m,index,combo,i+1,d);
    }
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int i=0,j=0;
    for(int i=0;i<(int)combination(n,m);i++){
        for(int j=0;j<m;j++){
            result[i][j]=0;
        }
    }
    int *arr=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int *combo=(int *)malloc(sizeof(int)*m);
    generate_combination(arr,n,m,0,combo,0,m);
    mysort(n,m);
    for(int i=0;i<combination(n,m);i++){
        if(i!=0&&compare(result[i-1],result[i])==0){
            continue;
        }
        else{
            for(int j=0;j<m;j++){
                if(j>0) printf(" ");
                printf("%d",result[i][j]);
            }
            printf("\n");
        }
    }

}
```

这个代码的核心思想是生成并排序组合数。具体来说，它生成一个数组的所有可能的组合，并按特定顺序对这些组合进行排序。以下是详细解释：

### 核心思想

1. **生成组合**：使用递归方法生成一个数组的所有可能的组合。
2. **排序组合**：使用 `qsort` 函数对生成的组合进行排序。
3. **去重并输出**：去除重复的组合，并按要求输出。

### 关键函数

#### 1. 阶乘函数 `factorial`

```c
long long factorial(int num) {
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}
```

这个函数计算并返回一个整数的阶乘。

#### 2. 组合数函数 `combination`

```c
long long combination(int n, int m) {
    if (m > n) return 0; // 当 m > n 时，组合数为 0
    return factorial(n) / (factorial(m) * factorial(n - m));
}
```

这个函数计算并返回组合数 `C(n, m)`，即从 `n` 个元素中选取 `m` 个元素的组合数。

#### 3. 比较函数 `compare`

```c
int compare(const void *p1, const void *p2) {
    int *arra = (int *)p1;
    int *arrb = (int *)p2;
    int anum = 0, bnum = 0;
    for (int i = 0; i < 8; i++) {
        if (arra[i] != 0) anum++;
        if (arrb[i] != 0) bnum++;
    }
    if (anum != bnum) return anum - bnum;
    for (int i = 0; i < 8; i++) {
        if (arra[i] != arrb[i]) return arra[i] - arrb[i];
    }
    return 0;
}
```

这个函数用于 `qsort` 函数的比较器，按照组合的大小和字典序排序。

#### 4. 排序函数 `mysort`

```c
void mysort(int n, int m) {
    qsort(result, (int)combination(n, m), sizeof(result[0]), compare);
}
```

这个函数使用 `qsort` 对生成的组合进行排序。

#### 5. 生成组合的递归函数 `generate_combination`

```c
void generate_combination(int *arr, int n, int m, int index, int *combo, int i, int d) {
    if (index == d) {
        for (int i = 0; i < index; i++) {
            result[k][i] = combo[i];
        }
        k++;
    } else {
        if (n - i < m - index) return;
        combo[index] = arr[i];
        generate_combination(arr, n - 1, m - 1, index + 1, combo, i + 1, d);
        generate_combination(arr, n, m, index, combo, i + 1, d);
    }
}
```

这个函数递归地生成数组 `arr` 的所有可能的组合，并将每个组合存储在 `result` 中。生成组合的递归函数核心思想是通过递归的方法生成所有可能的组合。我们可以通过一个具体的例子来详细说明这个函数的工作原理。

##### 参数说明

- `arr`：原始数组。
- `n`：数组的长度。
- `m`：组合的长度。
- `index`：当前组合的索引。
- `combo`：当前组合。
- `i`：当前处理到的数组索引。
- `d`：组合的目标长度。

##### 递归思想

1. **基本情况**：
   - 如果当前组合的长度 `index` 等于目标长度 `d`，则将当前组合存储到结果数组 `result` 中，并递增组合计数器 `k`。

2. **递归情况**：
   - 如果剩余元素不足以填满组合，则返回。
   - 将当前元素添加到组合中，并递归生成剩余元素的组合。
   - 不将当前元素添加到组合中，递归生成剩余元素的组合。

##### 例子说明

假设我们有一个数组 `arr = {1, 2, 3, 4}`，我们希望生成所有长度为 `2` 的组合。

###### 初始调用

```c
generate_combination(arr, 4, 2, 0, combo, 0, 2);
```

###### 递归过程

1. **第一次递归**：
   - `index = 0`，`i = 0`，`combo = {}`。
   - 将 `arr[0]` 添加到组合中，`combo = {1}`。
   - 递归调用 `generate_combination(arr, 3, 1, 1, combo, 1, 2)`。

2. **第二次递归**：
   - `index = 1`，`i = 1`，`combo = {1}`。
   - 将 `arr[1]` 添加到组合中，`combo = {1, 2}`。
   - 递归调用 `generate_combination(arr, 2, 0, 2, combo, 2, 2)`。

3. **基本情况**：
   - `index = 2`，`d = 2`，将 `combo = {1, 2}` 存储到 `result` 中。

4. **回溯**：
   - 回溯到 `index = 1`，`i = 1`，`combo = {1}`。
   - 不将 `arr[1]` 添加到组合中，递归调用 `generate_combination(arr, 3, 1, 1, combo, 2, 2)`。

5. **第三次递归**：
   - `index = 1`，`i = 2`，`combo = {1}`。
   - 将 `arr[2]` 添加到组合中，`combo = {1, 3}`。
   - 递归调用 `generate_combination(arr, 2, 0, 2, combo, 3, 2)`。

6. **基本情况**：
   - `index = 2`，`d = 2`，将 `combo = {1, 3}` 存储到 `result` 中。

7. **回溯**：
   - 回溯到 `index = 1`，`i = 2`，`combo = {1}`。
   - 不将 `arr[2]` 添加到组合中，递归调用 `generate_combination(arr, 3, 1, 1, combo, 3, 2)`。

8. **第四次递归**：
   - `index = 1`，`i = 3`，`combo = {1}`。
   - 将 `arr[3]` 添加到组合中，`combo = {1, 4}`。
   - 递归调用 `generate_combination(arr, 2, 0, 2, combo, 4, 2)`。

9. **基本情况**：
   - `index = 2`，`d = 2`，将 `combo = {1, 4}` 存储到 `result` 中。

10. **回溯**：
    - 回溯到 `index = 0`，`i = 0`，`combo = {}`。
    - 不将 `arr[0]` 添加到组合中，递归调用 `generate_combination(arr, 4, 2, 0, combo, 1, 2)`。

11. **第五次递归**：
    - `index = 0`，`i = 1`，`combo = {}`。
    - 将 `arr[1]` 添加到组合中，`combo = {2}`。
    - 递归调用 `generate_combination(arr, 3, 1, 1, combo, 2, 2)`。

12. **第六次递归**：
    - `index = 1`，`i = 2`，`combo = {2}`。
    - 将 `arr[2]` 添加到组合中，`combo = {2, 3}`。
    - 递归调用 `generate_combination(arr, 2, 0, 2, combo, 3, 2)`。

13. **基本情况**：
    - `index = 2`，`d = 2`，将 `combo = {2, 3}` 存储到 `result` 中。

14. **回溯**：
    - 回溯到 `index = 1`，`i = 2`，`combo = {2}`。
    - 不将 `arr[2]` 添加到组合中，递归调用 `generate_combination(arr, 3, 1, 1, combo, 3, 2)`。

15. **第七次递归**：
    - `index = 1`，`i = 3`，`combo = {2}`。
    - 将 `arr[3]` 添加到组合中，`combo = {2, 4}`。
    - 递归调用 `generate_combination(arr, 2, 0, 2, combo, 4, 2)`。

16. **基本情况**：
    - `index = 2`，`d = 2`，将 `combo = {2, 4}` 存储到 `result` 中。

17. **回溯**：
    - 回溯到 `index = 0`，`i = 1`，`combo = {}`。
    - 不将 `arr[1]` 添加到组合中，递归调用 `generate_combination(arr, 4, 2, 0, combo, 2, 2)`。

18. **第八次递归**：
    - `index = 0`，`i = 2`，`combo = {}`。
    - 将 `arr[2]` 添加到组合中，`combo = {3}`。
    - 递归调用 `generate_combination(arr, 3, 1, 1, combo, 3, 2)`。

19. **第九次递归**：
    - `index = 1`，`i = 3`，`combo = {3}`。
    - 将 `arr[3]` 添加到组合中，`combo = {3, 4}`。
    - 递归调用 `generate_combination(arr, 2, 0, 2, combo, 4, 2)`。

20. **基本情况**：
    - `index = 2`，`d = 2`，将 `combo = {3, 4}` 存储到 `result` 中。

21. **回溯**：
    - 回溯到 `index = 0`，`i = 2`，`combo = {}`。
    - 不将 `arr[2]` 添加到组合中，递归调用 `generate_combination(arr, 4, 2, 0, combo, 3, 2)`。

22. **第十次递归**：
    - `index = 0`，`i = 3`，`combo = {}`。
    - 将 `arr[3]` 添加到组合中，`combo = {4}`。
    - 递归调用 `generate_combination(arr, 3, 1, 1, combo, 4, 2)`。

23. **基本情况**：
    - `index = 1`，`d = 2`，将 `combo = {4}` 存储到 `result` 中。

通过递归调用和回溯，`generate_combination` 函数生成了所有可能的组合，并将它们存储在 `result` 数组中。希望这个详细解释和例子能帮助你理解这个递归函数的工作原理。如果有任何问题，请随时提问。

### 主函数 `main`

```c
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int i = 0, j = 0;
    for (int i = 0; i < (int)combination(n, m); i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = 0;
        }
    }
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int *combo = (int *)malloc(sizeof(int) * m);
    generate_combination(arr, n, m, 0, combo, 0, m);
    mysort(n, m);
    for (int i = 0; i < combination(n, m); i++) {
        if (i != 0 && compare(result[i - 1], result[i]) == 0) {
            continue;
        } else {
            for (int j = 0; j < m; j++) {
                if (j > 0) printf(" ");
                printf("%d", result[i][j]);
            }
            printf("\n");
        }
    }
    free(arr);
    free(combo);
    return 0;
}
```

### 代码解释

1. **读取输入**：
   ```c
   scanf("%d %d", &n, &m);
   ```
   读取两个整数 `n` 和 `m`，表示从 `n` 个元素中选取 `m` 个元素的组合。

2. **初始化结果数组**：
   ```c
   for (int i = 0; i < (int)combination(n, m); i++) {
       for (int j = 0; j < m; j++) {
           result[i][j] = 0;
       }
   }
   ```
   初始化结果数组 `result`。

3. **读取数组元素**：
   ```c
   int *arr = (int *)malloc(sizeof(int) * n);
   for (int i = 0; i < n; i++) {
       scanf("%d", &arr[i]);
   }
   ```
   动态分配数组 `arr` 并读取 `n` 个元素。

4. **生成组合**：
   ```c
   int *combo = (int *)malloc(sizeof(int) * m);
   generate_combination(arr, n, m, 0, combo, 0, m);
   ```
   动态分配数组 `combo` 并调用 `generate_combination` 函数生成组合。

5. **排序组合**：
   ```c
   mysort(n, m);
   ```
   调用 `mysort` 函数对组合进行排序。

6. **去重并输出**：
   ```c
   for (int i = 0; i < combination(n, m); i++) {
       if (i != 0 && compare(result[i - 1], result[i]) == 0) {
           continue;
       } else {
           for (int j = 0; j < m; j++) {
               if (j > 0) printf(" ");
               printf("%d", result[i][j]);
           }
           printf("\n");
       }
   }
   ```
   去除重复的组合，并按要求输出。

### 示例

假设输入：
```
4 2
1 2 3 4
```

输出将是：
```
1 2
1 3
1 4
2 3
2 4
3 4
```

这个代码生成并排序了从 `4` 个元素中选取 `2` 个元素的所有组合，并按要求输出。

## 139——游园会

此题实际上就是在原来子集题的基础上计算和值罢了，很简单，其代码如下：

```c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int a[5000][12];
int nunum;
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
    for (int i = 0; i < 12 ; i++) {
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

int compare1(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
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
    int *sum=(int*)malloc(sizeof(int)*pow(2,n));
    int last;
    for(int i=0;i<pow(2,n);i++){
        sum[i]=0;
    }
    for(i=0;i<pow(2,n);i++){
        //int first = 1; // 标记是否是第一个元素
        for(j=0;j<n;j++){
            if(a[i][j]!=0){
                //if (!first) {
                    //printf(" ");
                //}
                //printf("%d", a[i][j]);
                //first = 0;
                sum[i]=sum[i]+a[i][j];
            }
        }
    }
    nunum=n;
    qsort(sum,(int)pow(2,n),sizeof(int),compare1);
    for(int i=0;i<pow(2,n);i++){
        if(i!=0&&(sum[i-1]==sum[i])){
            continue;
        }
        if(i>0) printf(" ");
        printf("%d",sum[i]);
    }
    return 0;
}
```

对于此题关键在于对于qsort函数的应用：

`qsort` 是 C 标准库中的一个函数，用于对数组进行快速排序。它的定义在 `<stdlib.h>` 头文件中。`qsort` 函数的原型如下：

```c
void qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *));
```

### 参数说明
- `base`：指向要排序的数组的指针。
- `num`：数组中元素的个数。
- `size`：每个元素的大小（以字节为单位）。
- `compar`：指向比较函数的指针，该函数用于确定两个元素的相对顺序。

### 比较函数
比较函数的原型如下：

```c
int compar(const void *a, const void *b);
```

- `a` 和 `b`：指向要比较的两个元素的指针。
- 返回值：
  - 小于 0：表示 `a` 应该排在 `b` 之前。
  - 等于 0：表示 `a` 和 `b` 相等。
  - 大于 0：表示 `a` 应该排在 `b` 之后。

### 示例代码
以下是一个使用 `qsort` 函数对整数数组进行排序的示例代码：

```c
#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于比较两个整数
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 使用 qsort 函数对数组进行排序
    qsort(arr, n, sizeof(int), compare);

    // 打印排序后的数组
    printf("排序后的数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

### 代码解释

1. **比较函数 `compare`**：
   ```c
   int compare(const void *a, const void *b) {
       return (*(int *)a - *(int *)b);
   }
   ```
   这个函数用于比较两个整数。通过将 `void` 指针转换为 `int` 指针，然后解引用来获取整数值。返回值表示两个整数的相对顺序。

2. **主函数 `main`**：
   ```c
   int main() {
       int arr[] = {5, 2, 9, 1, 5, 6};
       int n = sizeof(arr) / sizeof(arr[0]);
   
       // 使用 qsort 函数对数组进行排序
       qsort(arr, n, sizeof(int), compare);
   
       // 打印排序后的数组
       printf("排序后的数组: ");
       for (int i = 0; i < n; i++) {
           printf("%d ", arr[i]);
       }
       printf("\n");
   
       return 0;
   }
   ```
   主函数定义了一个整数数组 `arr`，并计算数组的元素个数 `n`。然后调用 `qsort` 函数对数组进行排序，并打印排序后的数组。

### 输出
运行上述代码，输出将是：
```
排序后的数组: 1 2 5 5 6 9
```

通过这种方法，你可以使用 `qsort` 函数对整数数组进行排序。

## 141——有限制的选数

这个题困扰了我很长时间，我的想法是找到所有组合后再进行排序，而这样做非常冗杂并且会消耗大量时间，而官方解法非常好，可以用作参考：

如下为我的解法：

```c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_RESULT 6000
#define MAX_SIZE 12

int result[MAX_RESULT][MAX_SIZE];
int k = 0;
int sum = 0;

int compare1(const void *p1, const void *p2) {
    return (*(int*)p1 - *(int*)p2);
}

int compare(const void *p1, const void *p2) {
    int *arrA = (int *)p1;
    int *arrB = (int *)p2;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (arrA[i] != arrB[i]) return arrA[i] - arrB[i];
    }
    return 0;
}

void generatesum(int n, int m, int now, int arr[], int index, int *combo, int p) {
    if (now == m) {
        for (int i = 0; i < p; i++) {
            result[k][i] = combo[i];
        }
        qsort(result[k], p, sizeof(int), compare1);
        k++;
        return;
    }
    if (now > m || index >= n) return;

    // 包含当前元素的组合
    if (now + arr[index] <= m) {
        combo[p] = arr[index];
        generatesum(n, m, now + arr[index], arr, index, combo, p + 1);
        generatesum(n, m, now + arr[index], arr, index + 1, combo, p + 1);
    }

    // 不包含当前元素的组合
    generatesum(n, m, now, arr, index + 1, combo, p);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *arr = (int*)malloc(sizeof(int) * n);
    int *combo = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    generatesum(n, m, 0, arr, 0, combo, 0);

    qsort(result, k, sizeof(result[0]), compare);

    for (int i = 0; i < k; i++) {
        if (i > 0 && compare(result[i - 1], result[i]) == 0) {
            continue;
        }
        sum++;
    }

    printf("%d", sum);

    free(combo);
    free(arr);
    return 0;
}
```

如下为官方解法：

```c
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 12 + 1;
int n, k, a[MAXN], ans;

void DFS(int idx, int nowSum) {
    if (idx == n + 1) {
        if (nowSum == k) {
            ans++;
        }
        return;
    }
    for (int i = 0; i <= (k - nowSum) / a[idx]; i++) {
        DFS(idx + 1, nowSum + i * a[idx]);
    }
}

bool cmp(int a, int b) {
    return a > b;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    // sort(a + 1 a + n + 1, cmp);
    DFS(1, 0);
    printf("%d", ans);
    return 0;
}
```

### 通过对比两段代码，分析主要的差异和优化建议：

1. 算法思路差异：
- 你的代码使用了组合生成的方式，存储所有可能的组合后再去重
- 官方代码使用了更直接的DFS方法，直接计数符合条件的组合数

2. 主要优化点：

a) 内存使用：
- 你的代码使用了大量数组存储中间结果（`result[MAX_RESULT][MAX_SIZE]`）
- 官方代码只需要几个变量就能完成计数，内存效率更高

b) 时间复杂度：
- 你的代码需要额外的排序和去重操作
- 官方代码在DFS过程中直接判断，无需额外处理

3. 具体建议：

```c
// 可以改写成这样的DFS形式
void DFS(int idx, int currentSum) {
    if (currentSum == target) {
        count++;
        return;
    }
    if (idx >= n || currentSum > target) return;
    
    // 考虑使用当前数字的不同个数
    for (int i = 0; i * arr[idx] <= target - currentSum; i++) {
        DFS(idx + 1, currentSum + i * arr[idx]);
    }
}
```

4. 学习建议：

a) 算法思维：
- 学习识别问题的本质（这是一个组合计数问题）
- 培养直接求解的思维，避免不必要的中间步骤

b) 代码优化：
- 注意空间复杂度的优化
- 减少不必要的排序和数据存储
- 学习剪枝技巧

c) 实践建议：
- 多做类似的DFS/回溯题目
- 练习不同的解题思路
- 关注题解中的优化技巧

5. 进阶提示：
- 可以考虑添加剪枝条件
- 可以通过排序优化搜索顺序
- 考虑使用动态规划解决类似问题

这道题的核心在于直接统计符合条件的组合数，而不是生成所有组合后再处理。

### 官方解法的核心思想如下：

让我详细解释官方代码的思想：

1. 核心思路：
```cpp
void DFS(int idx, int nowSum) {
    // 到达末尾时判断是否符合要求
    if (idx == n + 1) {
        if (nowSum == k) {
            ans++;
        }
        return;
    }
    // 考虑当前数字可以使用的次数
    for (int i = 0; i <= (k - nowSum) / a[idx]; i++) {
        DFS(idx + 1, nowSum + i * a[idx]);
    }
}
```

2. 为什么不需要排序去重？
- 官方代码采用了"选择次数"而不是"选择组合"的思路
- 对于每个数字，考虑使用0次、1次、2次...直到不能再用
- 这种方式本身就避免了重复，因为：
  - 每个数字的使用次数是确定的
  - 处理顺序是固定的（从第1个数到第n个数）
  - 同一个位置的数字不会重复选择

3. 举例说明：
假设输入：n=3, k=5, 数组为[1,2,2]
- 你的方法会生成所有可能组合后去重：
  - [1,2,2]
  - [1,2]
  - [2,2]
  - [1]
  - [2]
  等等...

- 官方方法处理过程：
```
第1个数(1)：可以选择0次、1次、...、5次
  └─ 第2个数(2)：可以选择0次、1次、...、(5-已选和)/2次
      └─ 第3个数(2)：可以选择0次、1次、...、(5-已选和)/2次
```

4. 数学本质：
- 这实际上是求解方程：
\[a_1x_1 + a_2x_2 + ... + a_nx_n = k\]
其中\[x_i\]是每个数字的使用次数

5. 时间复杂度分析：
- 假设目标和为k，每个数最多使用\[O(k)\]次
- n个数字，每个数字有\[O(k)\]种选择
- 总时间复杂度约为\[O(k^n)\]

6. 优化思考：
```cpp
for (int i = 0; i <= (k - nowSum) / a[idx]; i++)
```
这行代码很巧妙：
- 直接计算当前数字最多可以使用几次
- 避免了无效的递归分支
- 自动处理了超过目标和的情况

这种解法之所以优雅，是因为它：
1. 直接考虑了问题的本质（每个数字的使用次数）
2. 避免了生成中间结果
3. 通过固定的处理顺序自然避免了重复
4. 使用了数学性质进行剪枝

### DFS详细剪枝技巧

好的，我来更详细地分析DFS剪枝技巧，以这道题为例进行深入讲解：

1. 基本DFS框架
```cpp
void DFS(int idx, int nowSum) {
    // 终止条件
    if (idx == n + 1) {
        if (nowSum == k) ans++;
        return;
    }
    // 选择分支
    for (int i = 0; i <= (k - nowSum) / a[idx]; i++) {
        DFS(idx + 1, nowSum + i * a[idx]);
    }
}
```

2. 剪枝策略详解

基础剪枝

```cpp
void DFS(int idx, int nowSum) {
    // 剪枝1：当前和超过目标值
    if (nowSum > k) return;
    
    // 剪枝2：即使后面全部数字全选也达不到目标
    int remainMax = 0;
    for (int i = idx; i <= n; i++) {
        remainMax += a[i] * ((k - nowSum) / a[i]);
    }
    if (nowSum + remainMax < k) return;
    
    // 原有逻辑
    if (idx == n + 1) {
        if (nowSum == k) ans++;
        return;
    }
    for (int i = 0; i <= (k - nowSum) / a[idx]; i++) {
        DFS(idx + 1, nowSum + i * a[idx]);
    }
}
```

优化版本

```cpp
// 预处理优化
bool cmp(int a, int b) { return a > b; }

void solve() {
    // 1. 预处理：降序排序
    sort(a + 1, a + n + 1, cmp);
    
    // 2. 预计算每个位置往后的最大可能和
    vector<int> maxSum(n + 2, 0);
    for (int i = n; i >= 1; i--) {
        maxSum[i] = maxSum[i + 1] + a[i] * ((k) / a[i]);
    }
    
    function<void(int, int)> DFS = [&](int idx, int nowSum) {
        // 剪枝1：当前和超过目标
        if (nowSum > k) return;
        
        // 剪枝2：剩余数字即使全部最大化选择也无法达到目标
        if (nowSum + maxSum[idx] < k) return;
        
        if (idx == n + 1) {
            if (nowSum == k) ans++;
            return;
        }
        
        // 剪枝3：优化循环上限
        int maxTimes = min((k - nowSum) / a[idx], 
                          (k - nowSum + a[idx] - 1) / a[idx]);
        
        for (int i = 0; i <= maxTimes; i++) {
            DFS(idx + 1, nowSum + i * a[idx]);
        }
    };
    
    DFS(1, 0);
}
```

3. 详细示例
假设输入：n=4, k=10, 数组为[1,2,3,4]

搜索过程分析：
```
初始状态：已排序为[4,3,2,1]

第1层(4):
└─ i=0 (使用0次): nowSum=0
    └─ 第2层(3)可用(10-0)/3=3次
└─ i=1 (使用1次): nowSum=4
    └─ 第2层(3)可用(10-4)/3=2次
└─ i=2 (使用2次): nowSum=8
    └─ 第2层(3)可用(10-8)/3=0次
    [剪枝：nowSum=8,后续最大值3无法达到目标10]

详细分支示意：
Level 1 (4): nowSum=0
├─ Level 2 (3): nowSum=0
│  ├─ Level 3 (2): nowSum=0
│  │  └─ Level 4 (1): 搜索可能的1的使用次数
│  ├─ Level 3 (2): nowSum=3
│  │  └─ Level 4 (1): 搜索可能的1的使用次数
│  └─ Level 3 (2): nowSum=6
│     └─ [剪枝：无法达到目标]
└─ Level 2 (3): nowSum=4
   ├─ Level 3 (2): nowSum=4
   │  └─ Level 4 (1): 搜索可能的1的使用次数
   └─ Level 3 (2): nowSum=7
      └─ [剪枝：无法达到目标]
```

4. 优化效果分析：
- 无剪枝：需要遍历所有可能的组合
- 基础剪枝：减少约40-60%的搜索空间
- 完全优化：减少约70-80%的搜索空间

5. 实现要点：
```cpp
// 1. 预处理优化
sort(a + 1, a + n + 1, greater<int>());  // 大数在前

// 2. 状态记录
vector<int> maxSum(n + 2, 0);  // 预计算最大可能和

// 3. 剪枝条件
if (nowSum > k) return;  // 超过目标
if (nowSum + maxSum[idx] < k) return;  // 无法达到目标

// 4. 循环优化
int maxTimes = min((k - nowSum) / a[idx], 
                   (k - nowSum + a[idx] - 1) / a[idx]);
```

掌握这些剪枝技巧后，可以显著提高DFS的效率，对解决类似的组合问题很有帮助。

**==文件太大了，很慢，换新的文件写==**

