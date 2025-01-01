#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    printf("%d",n/100);
    printf(" ");
    printf("%d",n/10-(n/100)*10);
    printf(" ");
    printf("%d",n-(n/10)*10);
    return 0;
}