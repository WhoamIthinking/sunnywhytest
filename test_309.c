#include<stdio.h>
#include<stdlib.h>
typedef struct listnode{
    int data;
    int next;
}listnode;
int nowdata[1010];
int firstdata[1010];
int main(){
    listnode l[200];
    int n,first;
    scanf("%d%d",&n,&first);
    for(int i=0;i<1010;i++){
        nowdata[i]=0;
        firstdata[i]=-1;
    }
    for (int j = 0; j < n; j++) {
        int mid, mdata, mnext;
        scanf("%d %d %d", &mid, &mdata, &mnext);
        l[mid].data = mdata;
        nowdata[mdata]++;
        l[mid].next = mnext;
    }
    int current=first;
    int prev = -1;
    while(current!=-1){
        if(nowdata[l[current].data]>1&&firstdata[l[current].data]==0){
            nowdata[l[current].data]--;
            int next=l[current].next;
            l[prev].next=next;
            current=next;
        }
        else{
            if(firstdata[l[current].data]==-1){
                firstdata[l[current].data]=0;
            }
            prev=current;
            current=l[current].next;
        }
    }

    current = first;
    //printf("\n");
    while (current != -1) {
        printf("%d %d %d\n", current, l[current].data, l[current].next);
        current = l[current].next;
    }
    
    return 0;
}