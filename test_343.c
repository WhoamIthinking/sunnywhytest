#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
    int left;
    int right;
} TreeNode;

TreeNode tree[1000];
int n;

int is_full_tree(int root){
    if(root==-1){
        return 1;
    }
    if(tree[root].left==-1 && tree[root].right==-1){
        return 1;
    }
    if(tree[root].left!=-1 && tree[root].right!=-1){
        return is_full_tree(tree[root].left) && is_full_tree(tree[root].right);
    }
    return 0;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int left, right;
        scanf("%d %d", &left, &right);
        tree[i].left = left;
        tree[i].right = right;
    }

    if(is_full_tree(0)){
        printf("Yes");
    }
    else{
        printf("No");
    }

    return 0;
}