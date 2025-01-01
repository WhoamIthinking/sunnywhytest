#include <stdio.h>
int mian(){
    int n;
    int i=0;
    scanf("%d",&n);
    while(n!=1){
        if(n%2==0){
            n=n/2;
        }
        else{
            n=3*n+1;
        }
        i++;
    }
    printf("%d",i);
    return 0;
}