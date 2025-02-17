#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
    int left;
    int right;
} TreeNode;

TreeNode tree[1000];
int n;

int is_complete_tree(int root){
    if(root==-1){
        return 1;
    }
    int queue[1000];
    int front=0,rear=0;
    int is_null=0;
    queue[rear++]=root;
    while(front<rear){
        if(queue[front]==-1){
            int p=front+1;
            while(p<rear){
                if(queue[p]!=-1){
                    return 0;
                }
                p++;
            }
            return 1;
        }
        TreeNode t=tree[queue[front]];
        front++;
        queue[rear++]=t.left;
        queue[rear++]=t.right;
    }
    return 1;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int left, right;
        scanf("%d %d", &left, &right);
        tree[i].left = left;
        tree[i].right = right;
    }

    if(is_complete_tree(0)){
        printf("Yes");
    }
    else{
        printf("No");
    }

    return 0;
}