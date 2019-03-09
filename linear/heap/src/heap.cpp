#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int nodeCount;
    int heapSize;
    int *arr;
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
    h->arr = (int*)malloc(sizeof(int) * heapSize);
    h->heapSize = heapSize;
    h->nodeCount = 0;
}

void data_swap(int *n1, int *n2)
{
    int temp;

    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

/*
 * Inserts data into heap, this is a max heap implementation
 *
 * INPUT
 * 	h		-	Pointer to allocated heap memory where we are storing the heap data
 * 	n		-	Data to store
 */
void insert_heap(HEAP *h, int n)
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
    h->arr[lastNodeIndex] = n;
    printf ("Inserting %d\n", n);

    // And put node where it corresponds
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

/*
 * Keeps heap property for max heap
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

    if (left < h->nodeCount && h->arr[left] > h->arr[maxNode]) {
        maxNode = left;
    }

    if (right < h->nodeCount && h->arr[right] > h->arr[maxNode]) {
        maxNode = right;
    }

    if (maxNode != parentNode) {
        data_swap(&(h->arr[parentNode]), &(h->arr[maxNode]));
        heapify_recursive(h, maxNode);
    }
}

/*
 * Keeps heap property for max heap
 *
 * INPUT
 * 	h		-	Pointer to allocated heap memory where we are storing the heap data
 * 	parentNodeIndex	-	Node where we need to start heapifying the heap
 *
 * OUTPUT
 * 	None
 */
void heapify_iterative(HEAP *h, int parentNode)
{
    int maxNode = parentNode;
    int left = 0;
    int right = 0;

    while(1) {
	    printf ("in iterative\n");
	    left = (parentNode * 2) + 1;
	    right = (parentNode * 2) + 2;
	    if (left < h->nodeCount && h->arr[left] > h->arr[maxNode]) {
		    maxNode = left;
	    }

	    if (right < h->nodeCount && h->arr[right] > h->arr[maxNode]) {
		    maxNode = right;
	    }

	    if (maxNode != parentNode) {
		    data_swap(&(h->arr[parentNode]), &(h->arr[maxNode]));
		    parentNode = maxNode;
	    } else {
		    break;
	    }
    }
}

int return_max(HEAP *h)
{
    return h->arr[0];
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
    int maxNum = h->arr[rootIndex];

    if (h->nodeCount == 0) {
        printf("\nHeap is empty!\n");
        return 0;
    }
    if (h->nodeCount) {
	maxNum = return_max(h);
        h->arr[rootIndex] = h->arr[--h->nodeCount];
        h->arr[h->nodeCount] = 0;
        // Heapify on the root node
        //heapify_recursive(h, 0);
        heapify_iterative(h, 0);
    }
    return maxNum;
}


int main()
{
    HEAP h = { 0 };
    int arr[] = { 45, 12, 33, 3, 6 };
    int aSize = sizeof(arr) / sizeof(int);
    int i;
    init_heap(&h, aSize);

    for (i = 0; i < aSize; i++) {
        insert_heap(&h, arr[i]);
    }

    for (i = 0; i < aSize; i++) {
        printf("In loop - Max element %d\n", return_max(&h));
        delete_node(&h, 0);
    }
    printf("\n");

}
