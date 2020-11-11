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
#include "queue.h"

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
