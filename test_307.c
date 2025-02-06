#include<stdio.h>
#include<stdlib.h>

typedef struct listnode{
    int data;
    int next;
}listnode,*list;

int main(){
    listnode l[200];
    int mid,n,first,k,mdata,mnext;
    scanf("%d%d%d",&n,&first,&k);
    for(int j=0;j<n;j++){
        scanf("%d%d%d",&mid,&mdata,&mnext);
        l[mid].data=mdata;
        l[mid].next=mnext;
    }
    int p=first;int q;
    while(p!=-1){
        if(l[p].data!=k){
            q=p;
            p=l[p].next;
        }
        else{
            if(p==first){
                first=l[p].next;
            }
            else{
                l[q].next=l[p].next;
            }
            p=l[p].next;
        }
    }
    for(p=first;p!=-1;p=l[p].next){
        printf("%d %d %d\n",p,l[p].data,l[p].next);
    }
    return 0;
}