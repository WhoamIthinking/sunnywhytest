#include<stdio.h>
#include<stdlib.h>

typedef struct treenode{
    int data;
    struct treenode* left;
    struct treenode* right;
}treenode;

treenode* insert(treenode *root,int data){
    if(root==NULL){
        root=(treenode*)malloc(sizeof(treenode));
        root->data=data;
        root->left=NULL;
        root->right=NULL;
        return root;
    }
    if(data>root->data){
        root->right=insert(root->right,data);
    }
    else{
        root->left=insert(root->left,data);
    }
    return root;
}

void postfind(treenode *root,int flag){
    if(root==NULL){
        return;
    }
    flag++;
    postfind(root->left,flag);
    postfind(root->right,flag);
    printf("%d",root->data);
    if(flag>0){
        printf(" ");
    }
}


int main(){
    treenode *root=NULL;
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int data;
        scanf("%d",&data);
        root=insert(root,data);
    }
    postfind(root,-1);
    return 0;
}