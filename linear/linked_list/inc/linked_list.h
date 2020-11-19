#ifndef LINKED_LIST_H
#define LINKED_LIST_H
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
typedef struct node LIST;

struct node {
	int num;
	NODE *next;
};


NODE *create_node(int num);
int insert_data(LIST *q, int num);
int is_queue_empty(LIST *q);
void print_queue(LIST *q);
#endif // #ifndef LINKED_LIST_H
