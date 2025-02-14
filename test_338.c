#include<stdio.h>
#include<stdlib.h>

int pre[60];
int middle[60];
int level[60];
int preindex=0;

int find_root(int levelstart,int levelend,int mstart,int mend){
    for(int i=levelstart;i<=levelend;i++){
        for(int j=mstart;j<=mend;j++){
            if(level[i]==middle[j]){
                return level[i];
            }
        }
    }
    return -1;
}

void postorder(int levelstart,int levelend,int mstart,int mend){
    if(levelstart>levelend||mstart>mend){
        return;
    }
    int root=find_root(levelstart,levelend,mstart,mend);
    int rootindex;
    for(int i=mstart;i<=mend;i++){
        if(middle[i]==root){
            rootindex=i;
            break;
        }
    }
    pre[preindex]=root;
    preindex++;
    postorder(levelstart,levelend,mstart,rootindex-1);
    postorder(levelstart,levelend,rootindex+1,mend);
   
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&level[i]);
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