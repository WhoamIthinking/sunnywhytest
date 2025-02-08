#include <stdio.h>
#include <stdlib.h>

typedef struct listnode {
    int data;
    int next;
} listnode, *list;

int main() {
    listnode l[200];
    int n, first;
    scanf("%d %d", &n, &first);
    
    for (int j = 0; j < n; j++) {
        int mid, mdata, mnext;
        scanf("%d %d %d", &mid, &mdata, &mnext);
        l[mid].data = mdata;
        l[mid].next = mnext;
    }
    
    // 反转链表
    int prev = -1;
    int current = first;
    while (current != -1) {
        int next = l[current].next;
        l[current].next = prev;
        prev = current;
        current = next;
    }
    
    // 输出反转后的链表
    current = prev;
    while (current != -1) {
        printf("%d %d %d\n", current, l[current].data, l[current].next);
        current = l[current].next;
    }
    
    return 0;
}