#include<stdio.h>
int a[110][110];
int n;
int sum=0;

int is_empty(int x,int y){
    if(x<0||x>=n||y<0||y>=n){
        return 1;
    }
    for(int i=0;i<n;i++){
        if(a[x][i]==1) return 1;
        if(a[i][y]==1) return 1;
    }
    for(int i=0;x-i>=0&&y-i>=0;i++){
        if(a[x-i][y-i]==1) return 1;
    }
    for(int i=0;x+i<n&&y+i<n;i++){
        if(a[x+i][y+i]==1) return 1;
    }
    for (int i = 0; x - i >= 0 && y + i < n; i++) {
        if (a[x - i][y + i] == 1) return 1;
    }
    for (int i = 0; x + i < n && y - i >= 0; i++) {
        if (a[x + i][y - i] == 1) return 1;
    }
    return 0;
}

void n_queen(int now_num,int x,int y){
    if(now_num==n){
        sum++;
        return;
    }
    else{
        if(is_empty(x,y)==0){
            a[x][y]=1;
            n_queen(now_num+1,x+1,y);
            a[x][y]=0;
        }
    }
}
int main(){
    scanf("%d",&n);
    //n_queen(0,0,0);
    for(int i=0;i<n;i++){
        //for(int j=0;j<n;j++){
            n_queen(0,0,i);
        //}
    }
    printf("%d",sum);
    return 0;
}