#include <stdio.h>
#include <stdlib.h>

// 定义树节点结构体
typedef struct TreeNode {
    int data;
    struct TreeNode* firstChild;
    struct TreeNode* nextSibling;
} TreeNode;

int totalsum = 0;

// 递归计算路径和
void calnum(TreeNode* root, int nowsum) {
    if (root == NULL) {
        return;
    }
    nowsum ++;
    if (root->firstChild == NULL) {
        totalsum =totalsum+(nowsum-1)*root->data;
    }
    calnum(root->firstChild, nowsum);
    TreeNode *t=root->firstChild;
    while(t!=NULL){
        calnum(t->nextSibling, nowsum);
        t=t->nextSibling;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &tree[i].data);
        tree[i].firstChild = NULL;
        tree[i].nextSibling = NULL;
    }
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        TreeNode* prevChild = NULL;
        for (int j = 0; j < k; j++) {
            int child;
            scanf("%d", &child);
            if (prevChild == NULL) {
                tree[i].firstChild = &tree[child];
            } else {
                prevChild->nextSibling = &tree[child];
            }
            prevChild = &tree[child];
        }
    }
    calnum(&tree[0], 0);
    printf("%d\n", totalsum);
    free(tree);
    return 0;
}