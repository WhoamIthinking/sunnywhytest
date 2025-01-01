#include<stdio.h>
int main(){
    int i,j,k=-1000000,n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&j);
        if(j>=k){
            k=j;
        }
        else{
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}