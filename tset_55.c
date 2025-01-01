#include <stdio.h>
int main(){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    if(a+b>c&&a+c>b&&c+b>a&&a-b<c&&b-a<c&&a-c<b&&c-a<b&&b-c<a&&c-b<a&&a>0&&b>0&&c>0){
        printf("YES");
    }
    else{
        printf("NO");
    }
    return 0;
}