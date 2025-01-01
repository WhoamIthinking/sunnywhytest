#include<stdio.h>
int a[100][100];
void rotate(int x, int y,int k,int n){
    if(n<1){
        return;
    }
    int i=0;
    for(i=0;i<n;i++){
        a[x+i][y]=k;
        k++;
    }
    for(i=1;i<n;i++){
        a[x+n-1][y+i]=k;
        k++;
    }
    for(i=1;i<n;i++){
        a[x+n-1-i][y+n-1]=k;
        k++;
    }
    for(i=1;i<n-1;i++){
        a[x][y+n-1-i]=k;
        k++;
    }
    rotate(x+1,y+1,k,n-2);
}
int main(){
    int n;
    int k=1;
    scanf("%d",&n);
    rotate(0,0,k,n);
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n-1;j++){
            printf("%d ",a[j][i]);
        }
        printf("%d\n",a[n-1][i]);
    }
    return 0;
}