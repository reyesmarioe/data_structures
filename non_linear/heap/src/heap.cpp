/* 
 * Mario Reyes (mreye22)
 * CSC 482
 * 2/23/2023
 *
 * NOTE: This code is my own implementation
 *
 */	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int item;
	int priority;
}NODE;

typedef struct heap {
	int nodeCount;
	int heapSize;
	int *position;
	NODE *arr;
}HEAP;

int get_node_child_left(int parentNode)
{
    return (parentNode * 2) + 1;
}

int get_node_child_right(int parentNode)
{
    return (parentNode * 2) + 2;
}

int get_node_parent(int nodeIndex)
{
    return (nodeIndex - 1) / 2;
}

void print_heap(HEAP *h)
{
    int i;
    for (i = 0; i < h->nodeCount; i++) {
        printf("(Item %d, Priority %d, Position %d) ", 
               h->arr[i].item, h->arr[i].priority, h->position[h->arr[i].item]);

    }
    printf ("\n");
}

/*
 * Initializes the heap. Heap allocated in heap memory (hope this is not too confusing)
 *
 * INPUT
 * 	h		-	Pointer to store allocated heap memory.
 * 	heapSize	-	Maximum size for the heap
 * OUTPUT
 * 	None
 */
void StartHeap(HEAP *h, int heapSize)
{
    printf ("Setting heap size to %d\n", heapSize);
    if (NULL == (h->arr = (NODE*)malloc(sizeof(NODE) * heapSize))) {
        printf ("malloc failed\n");
        return;
    }

    if (NULL == (h->position = (int*)malloc(sizeof(int) * heapSize))) {
        printf ("malloc failed\n");
        return;
    }

    h->heapSize = heapSize;
    h->nodeCount = 0;

    // Init hash table to know values
    memset((void*)h->position, -1, heapSize * sizeof(int));
}

int get_hash_key(HEAP *h, int value)
{
    return value % h->heapSize;
}

void data_swap(NODE *n1, NODE *n2)
{
    NODE temp;

    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int save_item_position(HEAP *h, int item, int itemPosition)
{
    int hashIndex = 0;

    hashIndex = get_hash_key(h, item);
    printf ("item %d, itemPostion %d, hashIndex %d\n", 
            item, itemPosition, hashIndex);

    printf ("Hash Index %d\n", h->position[hashIndex]);
    h->position[hashIndex] = itemPosition;
    printf ("Position %d saved\n", h->position[hashIndex]);
    return 0;
}
/*
 * Inserts data into heap
 *
 * INPUT
 * 	h		-	Pointer to allocated heap memory where we are storing the heap data
 * 	n		-	Data to store
 */
int Insert(HEAP *h, int item, int priority)
{
    int parentNodeIndex, lastNodeIndex;

    if (NULL == h) {
        printf("No heap memory allocated");
        return -1;
    }

    if (h->nodeCount > h->heapSize) {
        printf("Heap is full %d\n", h->nodeCount + 1);
        return -1;
    }

    // Insert node to last available position first
    lastNodeIndex = h->nodeCount++;
    printf ("lastNodeIndex %d, item %d, priority %d\n", lastNodeIndex, item, priority);
    h->arr[lastNodeIndex].item = item;
    h->arr[lastNodeIndex].priority = priority;

    // And put node where it corresponds
    while (lastNodeIndex) {
        parentNodeIndex = (lastNodeIndex - 1) / 2;

        if (h->arr[parentNodeIndex].priority <= h->arr[lastNodeIndex].priority) {
            break;
        }

        /*
         * move value up in the heap
         */
        data_swap(&(h->arr[parentNodeIndex]), &(h->arr[lastNodeIndex]));
        lastNodeIndex = parentNodeIndex;
    }
    // Keep track of where items are stored
    save_item_position(h, item, lastNodeIndex);
    return 0;
}

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
void HeapifyDown(HEAP *h, int parentNode)
{
    int position = 0;
    int maxNode = parentNode;
    int left = (parentNode * 2) + 1;
    int right = (parentNode * 2) + 2;

    if (left < h->nodeCount && h->arr[left].priority < h->arr[maxNode].priority) {
        maxNode = left;
    }

    if (right < h->nodeCount && h->arr[right].priority < h->arr[maxNode].priority) {
        maxNode = right;
    }

    if (maxNode != parentNode) {
        data_swap(&(h->arr[parentNode]), &(h->arr[maxNode]));
        position = h->position[h->arr[parentNode].item];
        h->position[h->arr[parentNode].item] = h->position[h->arr[maxNode].item];
        h->position[h->arr[maxNode].item] = position;
        HeapifyDown(h, maxNode);
    }
}

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
void HeapifyUp(HEAP *h, int parentNode)
{
    int position = 0;
    int maxNode = parentNode;
    int left = (parentNode * 2) + 1;
    int right = (parentNode * 2) + 2;

    if (left < h->nodeCount && h->arr[left].priority > h->arr[maxNode].priority) {
        maxNode = left;
    }

    if (right < h->nodeCount && h->arr[right].priority > h->arr[maxNode].priority) {
        maxNode = right;
    }

    if (maxNode != parentNode) {
        data_swap(&(h->arr[parentNode]), &(h->arr[maxNode]));
        position = h->position[h->arr[parentNode].item];
        h->position[h->arr[parentNode].item] = h->position[h->arr[maxNode].item];
        h->position[h->arr[maxNode].item] = position;
        HeapifyUp(h, maxNode);
    }
}

int FindMin(HEAP *h)
{
    return h->arr[0].item;
}

/*
 * Deletes a node, and keeps heap property.
 *
 * INPUT
 * 	h		-	Pointer to allocated heap memory where we are storing the heap data
 * 	nodeIndex	-	Node to retrieve
 * OUTPUT
 * 				Value of node
 */
int Delete(HEAP *h, int nodeIndex)
{
    int minNum = 0;

    if (!h->nodeCount) {
        printf("\nHeap is empty!\n");
        return 0;
    }

    minNum = h->arr[nodeIndex].item;

    lastItem = h->arr[h->nodeCount - 1].item;


    HeapifyDown(h, 0);

    // Decrease number of nodes
    --h->nodeCount;
    return minNum;
}

int ExtractMin(HEAP *h)
{
    Delete(h, 0);
    return 0;
}

int DeleteItem(HEAP *h, int item)
{
    Delete(h, h->position[item]);
    return 0;
}

int ChangeKey(HEAP *h, int item, int priority)
{
    int currentPriority = 0;
    int currentItem = 0;
    int currentItemPosition = 0;
    int lastItem = 0;
    int lastItemPosition = 0;
    int position = 0;

    currentPriority = h->arr[h->position[item]].priority;
    currentItemPosition = h->position[item];
    h->arr[h->position[item]].priority = priority;

    currentItem = h->arr[h->position[item]].item;
    lastItem = h->arr[h->nodeCount - 1].item;
    lastItemPosition = h->position[lastItem];

    data_swap(&(h->arr[h->position[item]]), &(h->arr[h->nodeCount - 1]));
    position = h->position[item];
    h->position[item] = h->position[lastItem];
    h->position[lastItem] = position;

    if (currentPriority < priority) {
        printf ("HeapifyDown\n");
        HeapifyDown(h, 0);
    } else {
        printf ("HeapifyUp\n");
        HeapifyDown(h, 0);
    }
    return 0;
}


void print_pos(HEAP *h)
{
    int i = 0;

    for (; i < h->nodeCount; i++) {
        if (h->position[h->arr[i].item] != -1) {
            printf ("%d - Position %d\n", i, h->position[h->arr[i].item]);
        }
    }
}

int main()
{
#define HEAP_SIZE 1000
	HEAP h;
	int arr[] = { 45, 12, 33, 3, 6 };
	StartHeap(&h, HEAP_SIZE);

	Insert(&h, arr[1], 10);
	Insert(&h, arr[0], 11);
	Insert(&h, arr[2], 12);
	Insert(&h, arr[3], 13);
	Insert(&h, arr[4], 14);
	print_heap(&h);
	print_pos(&h);

	print_heap(&h);
	ChangeKey(&h, 12, 144);
	ChangeKey(&h, 45, 385);
	ChangeKey(&h, 12, 2);
	ChangeKey(&h, 33, 22);
	print_heap(&h);
	DeleteItem(&h, 33);
	DeleteItem(&h, 45);
	return 0;
}
