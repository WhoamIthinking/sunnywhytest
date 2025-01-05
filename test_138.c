#include <stdio.h>
#include <stdlib.h>
#include<string.h>
char a[45000][8];
int k=0;
// 迭代计算阶乘的函数
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

void swap(char *a,char *b){
    char temp=*a;
    *a=*b;
    *b=temp;
}
int compare(const void *p1,const void *p2){
    char *arra=(char*)p1;
    char* arrb=(char*)p2;
    int anum=0,bnum=0;
    for(int i=0;i<8;i++){
        if(arra[i] != '0') anum++;
        if(arrb[i] != '0') bnum++;
    }
    if(anum!=bnum) return anum-bnum;
    for(int i=0;i<8;i++){
        if(arra[i] != arrb[i]) return arra[i] - arrb[i];
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
                printf("%c",a[i][j]);
            }
            printf("\n");
        }
    }
}

void permute(char* arr,int start,int end){
    if(start==end){
        for(int i=0;i<=end;i++){
            a[k][i]=arr[i];
            //strcpy(a[k][i],arr[i]);
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
    //int n;
    //scanf("%d",&n);
    char *arr=(char*)malloc(sizeof(char)*10);
    scanf("%s",arr);
    int n=strlen(arr);
    for(int i=0;i<(int)factorial(n);i++){
        for(int j=0;j<n;j++){
            a[i][j] = '0';
        }
    }
    permute(arr,0,n-1);
    mysort(n);
    printmute(n);
    return 0;
}