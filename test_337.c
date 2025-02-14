#include<stdio.h>
#include<stdlib.h>

int pre[60];
int middle[60];
int post[60];
int preindex=0; 
void postorder(int poststart,int postend,int mstart,int mend){
    if(poststart>postend){
        return;
    }
    int root=post[postend];
    int rootindex;
    for(int i=mstart;i<=mend;i++){
        if(middle[i]==root){
            rootindex=i;
            break;
        }
    }
    pre[preindex]=root;
    preindex++;
    postorder(poststart,poststart+rootindex-mstart-1,mstart,rootindex-1);
    postorder(poststart+rootindex-mstart,postend-1,rootindex+1,mend);
   
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&post[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&middle[i]);
    }
    postorder(0,n-1,0,n-1);
    for(int i=0;i<n;i++){
        if(i>0){
            printf(" ");
        }
        printf("%d",pre[i]);
    }
    return 0;
}