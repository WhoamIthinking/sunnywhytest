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
        arr[i]=i+1;
    }
    int *combo=(int *)malloc(sizeof(int)*m);
    generate_combination(arr,n,m,0,combo,0,m);
    mysort(n,m);
    for(int i=0;i<combination(n,m);i++){
        for(int j=0;j<m;j++){
            if(j>0) printf(" ");
            printf("%d",result[i][j]);
        }
        printf("\n");
    }

}