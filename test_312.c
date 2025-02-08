#include <stdio.h>
#include <stdlib.h>

typedef struct listnode {
    int data;
    int next;
} listnode, *list;

int main() {
    listnode l[200];
    listnode a[200];
    int n, first;
    scanf("%d %d", &n, &first);
    
    for (int j = 0; j < n; j++) {
        int mid, mdata, mnext;
        scanf("%d %d %d", &mid, &mdata, &mnext);
        l[mid].data = mdata;
        a[mid].data=mdata;
        a[mid].next=mnext;
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
    current = prev;int acurrent=first;
    while (current != -1&&acurrent!=-1) {
        if(l[current].data!=a[acurrent].data){
            printf("No\n");
            return 0;
        }
        current=l[current].next;
        acurrent=a[acurrent].next;
    }
    printf("Yes\n");
    return 0;
}