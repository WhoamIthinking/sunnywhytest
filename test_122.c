#include<stdio.h>
#include<math.h>
char a[3000][3000];
int mydivide(int n,int x, int y){
    if(n==1){
        a[x][y]='X';
        return 1;
    }
    else{
        int i=mydivide(n-1,x,y);
        mydivide(n-1,x,y+2*i);
        mydivide(n-1,x+i,y+i);
        mydivide(n-1,x+2*i,y);
        mydivide(n-1,x+2*i,y+2*i);
        return pow(3,n-1);
    }
}
int main(){
    int n;
    int i,j;
    scanf("%d",&n);
    int t=pow(3,n-1);
    for(i=1;i<=t;i++){
        for(j=1;j<=t;j++){
            a[i][j]=' ';
        }
    }
    mydivide(n,1,1);
    for(i=1;i<=t;i++){
        for(j=1;j<=t;j++){
            printf("%c",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}