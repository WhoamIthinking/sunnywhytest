#include<stdio.h>
#include<stdlib.h>

typedef struct treenode{
    int data;
    struct treenode* left;
    struct treenode* right;
}treenode;

treenode* findlowestancester(treenode *root,int p,int q){
    if(root==NULL){
        return NULL;
    }
    if(root->data==p||root->data==q){
        return root;
    }
    treenode *leftlowancester=findlowestancester(root->left,p,q);
    treenode *rightlowancester=findlowestancester(root->right,p,q);
    if(leftlowancester!=NULL&&rightlowancester!=NULL){
        return root;
    }
    if(leftlowancester!=NULL){
        return leftlowancester;
    }
    else{
        return rightlowancester;
    }
}

int main(){
    int n,p,q;
    scanf("%d %d %d",&n,&p,&q);
    treenode* tree=(treenode*)malloc(sizeof(treenode)*n);
    for(int i=0;i<n;i++){
        int left,right;
        scanf("%d %d",&left,&right);
        tree[i].data=i;
        if(left!=-1){
            tree[i].left=&tree[left];
        }
        else{
            tree[i].left=NULL;
        }
        if(right!=-1){
            tree[i].right=&tree[right];
        }
        else{
            tree[i].right=NULL;
        }  
    }
    treenode* ancester=findlowestancester(&tree[0],p,q);
    if(ancester!=NULL){
        printf("%d",ancester->data);
    }
    else{
        printf("-1");
    }
    free(tree);
    return 0;
}