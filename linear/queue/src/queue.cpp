/*
    Simple queue implementation
    Tail                      Head
    +----+----+----+----+----+
    |    |    |    |    |    |
    +----+----+----+----+----+
    queue operation occurs in the tail
    dequeue operations occur in the head


    This is essentially a linked list, with pointers
    to the head and tail
*/

#include<stdio.h>
#include<stdlib.h>

#define UNUSED(expr) do { (void)(expr); } while (0)

#define VERIFY(x) if (!(x)) {\
		  	nErr = -1;\
			goto bail;\
		  }

typedef struct node NODE;
typedef struct queue QUEUE;

struct node {
	int num;
	NODE *next;
};

struct queue {
	NODE *head;
	NODE *tail;
};

NODE *create_node(int num)
{
	NODE *newNode = NULL;
        int nErr = 0;

        UNUSED(nErr);
	VERIFY(NULL != (newNode = (NODE*)malloc(sizeof(NODE))));

	newNode->num = num;
	newNode->next = NULL;
bail:
	return newNode;
}

int enqueue(QUEUE *q, int num)
{
	NODE *newNode = NULL;
	int nErr = 0;

	VERIFY(NULL != (newNode = create_node(num)));
	if (q->tail) {
		q->tail->next = newNode;
		q->tail = q->tail->next;
	} else {
		q->head = q->tail = newNode;
	}
bail:
	return nErr;
}

int is_queue_empty(QUEUE *q)
{
	return (NULL == q->head);
}

int dequeue(QUEUE *q)
{
	NODE *tmp = NULL;
        int num = 0;

	if (is_queue_empty(q)) {
		printf ("queue is empty\n");
		return 0;
	}

	tmp = q->head;
	q->head = q->head->next;
	printf ("dequeue node %d\n", tmp->num);
        num = tmp->num;
        free(tmp);
        return num;
}

void print_queue(QUEUE *q)
{
	NODE *tmpHead = q->head;

	while(tmpHead) {
		printf ("%d ", tmpHead->num);
		tmpHead = tmpHead->next;
	}
	printf ("\n");
}

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

int main(void)
{
	QUEUE q = {NULL, NULL};
	int testNums [] = {3, 4, 12, 98, 7,90, 23, 27, 65, 89, 10, 12};
	unsigned int i = 0;


	dequeue(&q);
	for (i = 0; i < ARRAY_SIZE(testNums); i++) {
		enqueue(&q, testNums[i]);
	}

	print_queue(&q);
	dequeue(&q);
	print_queue(&q);
	dequeue(&q);
	print_queue(&q);
	dequeue(&q);
	print_queue(&q);
	dequeue(&q);
	print_queue(&q);
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	return 0;
}
