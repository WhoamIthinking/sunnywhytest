#include<stdio.h>
int mulnum(int n){
    if(n==1){
        return 0;
    }
    else{
        int i=1;
        int p=n/2;
        int t=0;
        for(i=1;i<=p;i++){
            t++;
            if(i==1){
                t+=mulnum(n-i);
            }
        }
        return t;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    printf("%d",mulnum(n));
    return 0;
}