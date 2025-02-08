#include<stdio.h>
#include<stdlib.h>
typedef struct listnode{
    int data;
    int next;
}listnode;
int nowdata[1010];
int main(){
    listnode l[200];
    int n,first;
    scanf("%d%d",&n,&first);
    for(int i=0;i<1010;i++){
        nowdata[i]=0;
    }
    int total=1;
    int a=0;int b=0;
    for (int j = 0; j < n; j++) {
        int mid, mdata, mnext;
        scanf("%d %d %d", &mid, &mdata, &mnext);
        l[mid].data = mdata;
        nowdata[mdata]++;
        l[mid].next = mnext;
    }
    int current=first;
    n=0;
    while(current!=-1){
        n++;
        current=l[current].next;
    }
    current=first;
    while(current!=-1){
        if(total==n/2){
            a=l[current].data;
        }
        if(total==n/2+1){
            b=l[current].data;
        }
        current=l[current].next;
        total++;
    }
    float c;
    if(n%2==1){
        c=(float)b;
    }
    else{
        c=(float)(a+b)/2;
    }
    printf("%.1f",c);
    return 0;
}