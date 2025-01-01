#include<stdio.h>
#include<math.h>
char a[3000][3000];
int sbinser(int n, int x,int y){
    if(n==1){
        a[x][y]=' ';
        return 1; 
    }
    else{
        int i=sbinser(n-1,x,y);
        sbinser(n-1,x,y+i);
        sbinser(n-1,x,y+2*i);
        sbinser(n-1,x+i,y);
        sbinser(n-1,x+i,y+2*i);
        sbinser(n-1,x+2*i,y);
        sbinser(n-1,x+2*i,y+i);
        sbinser(n-1,x+2*i,y+2*i);
        int j=0,k=0;
        for(j=x+i;j<x+i+pow(3,n-2);j++){
            for(k=y+i;k<y+i+pow(3,n-2);k++){
                a[j][k]='X';
            }
        }
        return pow(3,n-1);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int i=0,j=0;
    int t=pow(3,n-1);
    for(j=0;j<=t+1;j++){
        a[0][j]='+';
        a[t+1][j]='+';
    }
    for(i=1;i<=t;i++){
        a[i][0]='+';
        a[i][t+1]='+';
    }
    for(i=1;i<=t;i++){
        for(j=1;j<=t;j++){
            a[i][j]=' ';
        }
    }
    sbinser(n,1,1);
    for(i=0;i<=t+1;i++){
        for(j=0;j<=t+1;j++){
            printf("%c",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}