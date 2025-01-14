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