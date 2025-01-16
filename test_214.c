#include<stdio.h>
#include<math.h>
int main(){
    int n;
    scanf("%d",&n);
    int p=(int)sqrt(n);
    int s=0;
    for(int i=1;i<=p;i++){
        if(n%i==0){
            s+=2;
        }
    }
    printf("%d",s);
    return 0;
}