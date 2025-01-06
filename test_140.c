#include<stdio.h>
#include<stdlib.h>
//int result[5000];
int k=0;
int sum;
void generatesum(int n,int m,int now,int arr[],int index){
    if(now==m){
        sum++;
        return;
    }
    else{
        if(now>m||index>n) return;
        //result[k]=arr[index];
        //k++;
        generatesum(n,m,now+arr[index],arr,index+1);
        generatesum(n,m,now,arr,index+1);
    }
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int *arr=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    generatesum(n,m,0,arr,0);
    printf("%d",sum);
    free(arr);
    return 0;
}