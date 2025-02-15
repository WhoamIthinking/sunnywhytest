#include<stdio.h>
#include<stdlib.h>

typedef struct treenode{
    int data;
    struct treenode* left;
    struct treenode* right;
}treenode;

int totalsum=0;

void calnum(treenode* root,int nowsum){
    if(root==NULL){
        return;
    }
    nowsum+=root->data;
    if(root->left==NULL&&root->right==NULL){
        totalsum+=nowsum;
    }
    calnum(root->left,nowsum);
    calnum(root->right,nowsum);
}

int main(){
    int n;
    scanf("%d",&n);
    treenode* tree=(treenode*)malloc(sizeof(treenode)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&tree[i].data);
    }
    for(int i=0;i<n;i++){
        int left,right;
        scanf("%d %d",&left,&right);
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
    calnum(&tree[0],0);
    printf("%d",totalsum);
    free(tree);
    return 0;
}