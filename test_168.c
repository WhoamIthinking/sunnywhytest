#include<stdio.h>
#include<stdlib.h>
int find_rotation_point(long int a[],int n){
    int front=0;
    int end=n-1;
    while(front<end){
        int middle=(front+end)/2;
        if(a[middle]>a[end]){
            front=middle+1;
        }
        else{
            end=middle;
        }
    }
    return front;
}
float find_middle_num(long int a[],int n,int r){
    int p=(n-1)/2;
    if(n%2==1){
        int s=(r+p)%n;
        return (float)a[s];
    }
    else{
        int s=(r+p)%n;
        int m=(r+p+1)%n;
        return (a[s]+a[m])/2.0;
    }
}
int main(){
    int n;
    scanf("%d", &n);
    long int *arr = (long int *)malloc(sizeof(long int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%ld", &arr[i]);
    }
    int rotation_point = find_rotation_point(arr, n);
    float median = find_middle_num(arr, n, rotation_point);
    printf("%.1f\n", median);
    free(arr);
    return 0;
}