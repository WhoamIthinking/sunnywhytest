#include <stdio.h>
#include <stdlib.h>

typedef struct HEAP {
    int *data;
    int size;
} heap;

heap* heap_create(int n) {
    heap *h = (heap*)malloc(sizeof(heap));
    h->data = (int *)malloc(sizeof(int) * (n + 1));
    h->size = 0;
    return h;
}

void heap_sift_up(heap *h, int idx) {
    while (idx > 1 && h->data[idx] < h->data[idx / 2]) {
        int temp = h->data[idx];
        h->data[idx] = h->data[idx / 2];
        h->data[idx / 2] = temp;
        idx /= 2;
    }
}

void heap_sift_down(heap *h, int idx) {
    while (2 * idx <= h->size) {
        int j = 2 * idx;
        if (j < h->size && h->data[j] > h->data[j + 1]) {
            j++;
        }
        if (h->data[idx] <= h->data[j]) {
            break;
        }
        int temp = h->data[idx];
        h->data[idx] = h->data[j];
        h->data[j] = temp;
        idx = j;
    }
}

void heap_insert(heap *h, int value) {
    h->data[++h->size] = value;
    heap_sift_up(h, h->size);
}

int heap_delete_min(heap *h) {
    int min_value = h->data[1];
    h->data[1] = h->data[h->size--];
    heap_sift_down(h, 1);
    return min_value;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    heap *h = heap_create(n);
    for (int i = 0; i < n; i++) {
        heap_insert(h, a[i]);
    }

    for (int i = 0; i < k - 1; i++) {
        heap_delete_min(h);
    }

    int p = heap_delete_min(h);
    printf("%d\n", p);

    free(a);
    free(h->data);
    free(h);
    return 0;
}