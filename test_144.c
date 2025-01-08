#include<stdio.h>
#include<stdlib.h>
int n;
int result[40000][30];
int k=0;
void match(int now,int count1,int count2){
    if((now==2*n)){
        if(count1+count2==0){
            k++;
            for(int i=0;i<2*n;i++){
                result[k][i]=result[k-1][i];
            }
        }
        return;
    }
    else{
        if(count1+count2>0){
            result[k][now]=1;
            match(now+1,count1+1,count2);
            result[k][now]=-1;
            match(now+1,count1,count2-1);
        }
        else{
            result[k][now]=1;
            match(now+1,count1+1,count2);
        }
    }
}
int main(){
    scanf("%d",&n);
    match(0,0,0);
    for(int i=0;i<k;i++){
        for(int j=0;j<2*n;j++){
            //printf("%d ",result[i][j]);
            if(result[i][j]==1){
                printf("(");
            }
            else{
                printf(")");
            }
        }
        printf("\n");
    }
    return 0;
}