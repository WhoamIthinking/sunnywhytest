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