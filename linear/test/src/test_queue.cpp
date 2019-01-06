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
