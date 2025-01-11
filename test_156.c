#include<stdio.h>
#include<stdlib.h>
int find_rotatation(int arr[],int num,int n){
    int front=0;
    int end=n-1;
    while(front<end){
        int middle=(front+end)/2;
        if(arr[middle]==num){
            return middle;
        }
        if(arr[middle]>arr[front]){
            if(num>arr[front]&&num<arr[middle]){
                end=middle-1;
            }
            else{
                front=middle+1;
            }

        }
        else{
            if(num<arr[end]&&num>arr[middle]){
                front=middle+1;
            }
            else{
                end=middle-1;
            }
        }
    }
    return -1;
}
int main(){
    int n,x;
    scanf("%d %d",&n,&x);
    int *arr=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int p=find_rotatation(arr,x,n);
    printf("%d",p);
    return 0;
}