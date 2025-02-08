#include<stdio.h>
#include<stdlib.h>
typedef struct listnode{
    int data;
    int next;
}listnode;
int nowdata[1010];
int main(){
    listnode l[200];
    int n,first,k;
    scanf("%d%d%d",&n,&first,&k);
    for(int i=0;i<1010;i++){
        nowdata[i]=0;
    }
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
    k=n-k+1;
    int total=1;
    while(current!=-1){
        if(total==k){
            break;
        }
        current=l[current].next;
        total++;
    }
    printf("%d %d %d\n",current,l[current].data,l[current].next);
    return 0;
}