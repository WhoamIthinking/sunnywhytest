#include<stdio.h>
#include<stdlib.h>
int n,m;
int count=0;
int arr[100];
int chongfu[200];
void selectnum(int index,int now){
    if(index>=n){
        if(now==m){
            count++;
        }
        return;
    }
    else{
        while(index<n&&(arr[index]==arr[index+1])){
            index++;
           // chongfu++;
        }
        for(int i=0;i<=chongfu[arr[index]];i++){
            selectnum(index+1,i*arr[index]+now);
        }
        //chongfu=1;
    }
}
//int compare(const void *p1,const void *p2){
   // return (*(int*)p1-*(int*)p2);
//}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<200;i++){
        chongfu[i]=0;
    }
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        chongfu[arr[i]]++;
    }
   // qsort(arr,n,sizeof(int),compare);
    selectnum(0,0);
    printf("%d",count);
    return 0;
}