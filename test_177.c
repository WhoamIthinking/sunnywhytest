#include<stdio.h>
#include<stdlib.h>
int* merge(int *p1,int *p2,int m,int n){
    int *p=(int*)malloc(sizeof(int )*(m+n));
    int i=0,j=0,k=0;
    while(i<m&&j<n){
        if(p1[i]<=p2[j]){
            p[k]=p1[i];
            i++;
            k++;
        }
        else{
            p[k]=p2[j];
            j++;
            k++;
        }
    }
    while(i<m){
        p[k]=p1[i];
        i++;
        k++;
    }
    while(j<n){
        p[k]=p2[j];
        k++;
        j++;
    }
    return p;
}
int*  merge_sort(int *p,int left,int right){
    if (left == right) {
        int* t=(int*)malloc(sizeof(int));
        t[0]=p[left];
        return t;
    }
    if(left==right-1){
        int*t=merge(&p[left],&p[right],1,1);
        return t;
    }
    int mid=(left+right)/2;
    int *p1=merge_sort(p,left,mid);
    int *p2=merge_sort(p,mid+1,right);
    int *t=merge(p1,p2,mid-left+1,right-mid);
    free(p1);
    free(p2);
    return t;
}
int main(){
    int n;
    scanf("%d",&n);
    int* p=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&p[i]);
    }
    p=merge_sort(p,0,n-1);
    for(int i=0;i<n;i++){
        if(i>0){
            printf(" ");
        }
        printf("%d",p[i]);
    }
    free(p);
    return 0;
}