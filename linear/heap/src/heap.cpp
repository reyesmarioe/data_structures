#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int nodeCount;
    int heapSize;
    int *arr;
}HEAP;

void init_heap(HEAP *h, int s)
{
    printf ("Setting heap size to %d\n", s);
    h->arr = (int*)malloc(sizeof(int) * s);
    h->heapSize = s;
    h->nodeCount = 0;
}

void data_swap(int *n1, int *n2)
{
    int temp;

    temp = *n1;
    *n1 = *n2;
    *n2 = *n1;
}

void insert_heap(HEAP *h, int n)
{
    int parentNodeIndex, lastNodeIndex;
    int tempNode;

    if (h->heapSize <= h->nodeCount + 1) {
        printf("Heap is full %d\n", h->nodeCount + 1);
        return;
    }

    // Insert node to last available position first
    lastNodeIndex = h->nodeCount++;
    h->arr[lastNodeIndex] = n;

    while (lastNodeIndex) {
        parentNodeIndex = (lastNodeIndex - 1) / 2;

        /* 
         * This is a MAX HEAP ( note the '>')
         */
        if (h->arr[parentNodeIndex] >= h->arr[lastNodeIndex]) {
            break;
        }

        /*
         * move value up in the heap
         */
        data_swap(&(h->arr[parentNodeIndex]), &(h->arr[lastNodeIndex]));
        lastNodeIndex = parentNodeIndex;
    }

}


int heapify(HEAP *h, int parentNode)
{
    int maxNode = parentNode;
    int left = (parentNode * 2) + 1;
    int right = (parentNode * 2) + 2;

    if (left < h->nodeCount && h->arr[left] > h->arr[maxNode]) {
        maxNode = left;
    }

    if (right < h->nodeCount && h->arr[right] > h->arr[maxNode]) {
        maxNode = right;
    }

    if (maxNode != parentNode) {
        data_swap(&(h->arr[parentNode]), &(h->arr[maxNode]));
        heapify(h, maxNode);
    }
    return 0;
}

int return_max(HEAP *h)
{
    return h->arr[0];
}

int delete_node(HEAP *h)
{
    int rootIndex = 0;
    int maxNum = h->arr[rootIndex];
    if (h->nodeCount) {
        printf("Max element %d\n", return_max(h));
        h->arr[rootIndex] = h->arr[h->nodeCount--];;
        // Heapify on the root node
        heapify(h, rootIndex);
    } else {
        printf("\nHeap is empty!\n");
        return 0;
    }
    return maxNum;
}


int main()
{
    HEAP h = { 0 };
    int arr[] = { 3, 12, 33, 45, 6 };
    int aSize = sizeof(arr) / sizeof(int);
    int i;
    init_heap(&h, aSize);

    for (i = 0; i < aSize; i++) {
        insert_heap(&h, arr[i]);
    }

    for (i = 0; i < aSize; i++) {
        printf("Removing %d \n", delete_node(&h));
    }
    printf("\n");

}
