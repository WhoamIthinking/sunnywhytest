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

int is_same(treenode *root1,treenode* root2){
    if(root1==NULL&&root2==NULL){
        return 1;
    }
    if(root1==NULL||root2==NULL){
        return 0;
    }
    if(root1->data!=root2->data){
        return 0;
    }
    return 1&&is_same(root1->left,root2->left)&&is_same(root1->right,root2->right);
}


int main(){
    treenode *root1=NULL,*root2=NULL;
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int data;
        scanf("%d",&data);
        root1=insert(root1,data);
    }
    for(int i=0;i<n;i++){
        int data;
        scanf("%d",&data);
        root2=insert(root2,data);
    }
    if(is_same(root1,root2)){
        printf("Yes");
    }
    else{
        printf("No");
    }
    return 0;
}