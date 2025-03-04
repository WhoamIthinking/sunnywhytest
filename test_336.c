#include<stdio.h>
#include<stdlib.h>

int pre[60];
int middle[60];
int post[60];
int postindex=0; 
void postorder(int prestart,int preend,int mstart,int mend){
    if(prestart>preend){
        return;
    }
    int root=pre[prestart];
    int rootindex;
    for(int i=mstart;i<=mend;i++){
        if(middle[i]==root){
            rootindex=i;
            break;
        }
    }
    postorder(prestart+1,prestart+rootindex-mstart,mstart,rootindex-1);
    postorder(prestart+rootindex-mstart+1,preend,rootindex+1,mend);
    post[postindex++]=root;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&pre[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&middle[i]);
    }
    postorder(0,n-1,0,n-1);
    for(int i=0;i<n;i++){
        if(i>0){
            printf(" ");
        }
        printf("%d",post[i]);
    }
    return 0;
}