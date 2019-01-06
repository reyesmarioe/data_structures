#ifndef QUEUE_H
#define QUEUE_H
#include<stdio.h>
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

#define UNUSED(expr) do { (void)(expr); } while (0)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

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

NODE *create_node(int num);
int enqueue(QUEUE *q, int num);
int is_queue_empty(QUEUE *q);
int dequeue(QUEUE *q);
void print_queue(QUEUE *q);
#endif // #ifndef QUEUE_H
