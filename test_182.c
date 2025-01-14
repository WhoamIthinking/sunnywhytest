#include<stdio.h>
#include<stdlib.h>
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int* a=(int*)malloc(sizeof(int)*n);
    int *b=(int *)malloc(sizeof(int)*m);
    int *c=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<m;i++){
        scanf("%d",&b[i]);
    }
    int i=0,j=0,k=0;
    while(i<n&&j<m){
        if(a[i]<b[j]){
            c[k]=a[i];
            i++;k++;
        }
        else if(a[i]==b[j]){
            i++;j++;
        }
        else{
            j++;
        }
    }
    while(i<n){
        c[k]=a[i];
        i++;k++;
    }
    for(int i=0;i<k;i++){
        if(i>0){
            printf(" ");
        }
        printf("%d",c[i]);
    }
    free(a);
    free(b);
    free(c);
    return 0;
}