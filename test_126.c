#include<stdio.h>
#include<math.h>
int a[5000][12];
void chains(int n, int x, int y){
    if(n==1){
        a[x+1][y]=1;
        //printf("%d %d\n",x+1,y);
        return;
    }
    int i;
    for(i=1<<(n-1);i<1<<(n);i++){
        a[x+i][y]=1;
        //printf("%d %d\n",x+i,y);
    }
    chains(n-1,x,y+1);
    chains(n-1,x+(1<<(n-1)),y+1);
}
int main(){
    int n;
    scanf("%d",&n);
    int i,j;
    for(i=0;i<(1<<n);i++){
        for(j=0;j<n;j++){
            a[i][j]=0;
        }
    }
    chains(n,0,0);
    for(i=0;i<(1<<n);i++){
        for(j=0;j<n;j++){
            printf("%d",a[i][j]);
        }
        printf("\n");
    }

}