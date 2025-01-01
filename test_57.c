#include<stdio.h>
int main(){
    int n,i,j;
    scanf("%d",&n);
    int k=0;
    for(i=0;i<n;i++){
        scanf("%d",&j);
        if(j%2==1){
            k=k+j;
        }
    }
    printf("%d",k);
    return 0;
}