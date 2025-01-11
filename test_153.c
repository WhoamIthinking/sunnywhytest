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