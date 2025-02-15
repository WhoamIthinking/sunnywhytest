#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int left;
    int right;
} TreeNode;

TreeNode tree[1000];
int n;

void leftView(int root) {
    if (root == -1) return;

    int queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int count=0;
    while (front < rear) {
        int levelSize = rear - front;
        for (int i = 0; i < levelSize; i++) {
            int node = queue[front++];
            if (i == 0) {
                if(count>0){
                    printf(" ");
                }
                printf("%d", node);
            }
            if (tree[node].left != -1) {
                queue[rear++] = tree[node].left;
            }
            if (tree[node].right != -1) {
                queue[rear++] = tree[node].right;
            }
        }
        count++;
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int left, right;
        scanf("%d %d", &left, &right);
        tree[i].left = left;
        tree[i].right = right;
    }

    // 从根结点（编号为0）开始计算左视图
    leftView(0);

    return 0;
}