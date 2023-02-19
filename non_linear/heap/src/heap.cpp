/*
 * mreye22
 * CSC482
 * 02/19/2021
 *
 * This is my own source code.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int item;
    int orderingValue;
} NODE;

typedef struct heap {
    int nodeCount;
    int heapSize;

    NODE *arr;
}HEAP;

/*
 * Initializes the heap. Heap allocated in heap memory (hope this is not too confusing)
 *
 * INPUT
 * 	h		-	Pointer to store allocated heap memory.
 * 	heapSize	-	Maximum size for the heap
 * OUTPUT
 * 	None
 */
void init_heap(HEAP *h, int heapSize)
{
    printf ("Setting heap size to %d\n", heapSize);
    h->arr = (NODE*)malloc(sizeof(NODE) * heapSize);
    h->heapSize = heapSize;
    h->nodeCount = 0;
}

void data_swap(NODE *n1, NODE *n2)
{
    NODE temp;

    printf ("Swap\n");
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int heapify_down(HEAP *h, int lastNodeIndex)
{
    int parentNodeIndex = 0;

    // Put node where it corresponds
    while (lastNodeIndex) {
        parentNodeIndex = (lastNodeIndex - 1) / 2;

        printf("%d %d\n", h->arr[parentNodeIndex].orderingValue, h->arr[lastNodeIndex].orderingValue); 
        /* 
         * This is a MIN HEAP ( note the '<')
         */
        if (h->arr[parentNodeIndex].orderingValue <= h->arr[lastNodeIndex].orderingValue) {
            break;
        }

        /*
         * move value down in the heap
         */
        data_swap(&(h->arr[parentNodeIndex]), &(h->arr[lastNodeIndex]));
        lastNodeIndex = parentNodeIndex;
    }
}

/*
 * Inserts data into heap, this is a max heap implementation
 *
 * INPUT
 * 	h		-	Pointer to allocated heap memory where we are storing the heap data
 * 	n		-	Data to store
 */
void insert_heap(HEAP *h, int n, int orderingValue)
{
    int parentNodeIndex, lastNodeIndex;
    int tempNode;


    if (NULL == h) {
        printf("No heap memory allocated");
        return;
    }

    if (h->nodeCount > h->heapSize) {
        printf("Heap is full %d\n", h->nodeCount + 1);
        return;
    }

    // Insert node to last available position first
    lastNodeIndex = h->nodeCount++;
    h->arr[lastNodeIndex].item = n;
    h->arr[lastNodeIndex].orderingValue = orderingValue;
    printf ("Inserting %d, Ordering %d\n", n, orderingValue);

    heapify_down(h, lastNodeIndex);
}

#if 0
int heapify_up(HEAP *h, int lastNodeIndex)
{
    int parentNodeIndex = 0;

    // Put node where it corresponds
    while (lastNodeIndex) {
        parentNodeIndex = (lastNodeIndex - 1) / 2;

        /* 
         * This is a MAX HEAP ( note the '>')
         */
        if (h->arr->value[parentNodeIndex] >= h->arr->value[lastNodeIndex]) {
            break;
        }

        /*
         * move value up in the heap
         */
        data_swap(&(h->arr->value[parentNodeIndex]), &(h->arr->value[lastNodeIndex]));
        lastNodeIndex = parentNodeIndex;
    }
}

int heapify_down(HEAP *h, int lastNodeIndex)
{
    int parentNodeIndex = 0;

    // Put node where it corresponds
    while (lastNodeIndex) {
        parentNodeIndex = (lastNodeIndex - 1) / 2;

        /* 
         * This is a MIN HEAP ( note the '<')
         */
        if (h->arr->value[parentNodeIndex] <= h->arr->value[lastNodeIndex]) {
            break;
        }

        /*
         * move value up in the heap
         */
        data_swap(&(h->arr->value[parentNodeIndex]), &(h->arr->value[lastNodeIndex]));
        lastNodeIndex = parentNodeIndex;
    }
}

#endif
/*
 * Keeps heap property for min heap
 *
 * INPUT
 * 	h		-	Pointer to allocated heap memory where we are storing the heap data
 * 	parentNodeIndex	-	Node where we need to start heapifying the heap
 *
 * OUTPUT
 * 	None
 */
void heapify_recursive(HEAP *h, int parentNode)
{
    int maxNode = parentNode;
    int left = (parentNode * 2) + 1;
    int right = (parentNode * 2) + 2;

    if (left < h->nodeCount && h->arr[left].orderingValue > h->arr[maxNode].orderingValue) {
        maxNode = left;
    }

    if (right < h->nodeCount && h->arr[right].orderingValue > h->arr[maxNode].orderingValue) {
        maxNode = right;
    }

    if (maxNode != parentNode) {
        data_swap(&(h->arr[parentNode]), &(h->arr[maxNode]));
        heapify_recursive(h, maxNode);
    }
}

int find_min(HEAP *h)
{
    return h->arr[0].item;
}

/*
 * Retrieves a node, and keeps heap property.
 *
 * INPUT
 * 	h		-	Pointer to allocated heap memory where we are storing the heap data
 * 	nodeIndex	-	Node to retrieve
 * OUTPUT
 * 				Value of node
 */
int delete_node(HEAP *h, int nodeIndex)
{
    int rootIndex = 0;
    int maxNum = 0;
    int parentNodeIndex = 0;

    if (h->nodeCount == 0) {
        printf("\nHeap is empty!\n");
        return 0;
    }

    parentNodeIndex = (nodeIndex - 1) / 2;
    printf ("Delete node index %d\n", nodeIndex);
    if (h->nodeCount) {
	maxNum = h->arr[nodeIndex].item; 
        printf ("Value to delete %d\n", maxNum);
        //h->arr[rootIndex] = h->arr[nodeIndex];
        //h->arr[h->nodeCount].orderingValue = 0;
        // Heapify on the root node
        heapify_recursive(h, parentNodeIndex);
        --h->nodeCount;
    }
    return maxNum;
}

void print_heap(HEAP *h)
{
    int i = 0;
    for(; i < h->nodeCount; i++) {
        printf ("%d %d \n", h->arr[i].item, h->arr[i].orderingValue);
    }
}

int main()
{
    HEAP h = { 0 };
    int arr[] = { 1245, 12, 33, 3, 6, 100, 75 };
    int aSize = sizeof(arr) / sizeof(int);
    int i;
    init_heap(&h, aSize);

    insert_heap(&h, arr[1], 0);
    insert_heap(&h, arr[0], 1);
    insert_heap(&h, arr[3], 2);
    insert_heap(&h, arr[4], 3);
    insert_heap(&h, arr[2], 4);

    print_heap(&h);

    delete_node(&h, 2);
    print_heap(&h);
#if 0
    for (i = 0; i < aSize; i++) {
        printf("In loop - Max element %d\n", return_max(&h));
        delete_node(&h, 0);
    }
#endif
    printf("\n");

}
