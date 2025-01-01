#include<stdio.h>
int maxmul(int n){
    if(n==1){
        return 1;
    }
    else{
        int max=-9999;
        int i=1;
        int p=n/2;
        for(i=1;i<=p+1;i++){
            int m;
            if(maxmul(n-i)>n-i){
                m=maxmul(n-i);
            }
            else{
                m=n-i;
            }
            int t=i*m;
            if(max<t){
                max=t;
            }
        }
        return max;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    printf("%d",maxmul(n));
    return 0;
}