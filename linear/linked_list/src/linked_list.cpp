/*
    Simple linked linst implementation
    Head
    +----+----+    +----+----+     +----+----+    +----+----+
    |    |    |--->|    |    |---> |    |    |--->|    |    |--->NULL
    +----+----+    +----+----+     +----+----+    +----+----+

*/

#include<stdio.h>
#include<stdlib.h>
#include "linked_list.h"

NODE *create_node(int num)
{
	NODE *newNode = NULL;
        int nErr = 0;

        printf ("in create_node\n");
        UNUSED(nErr);
	VERIFY(NULL != (newNode = (NODE*)malloc(sizeof(NODE))));

	newNode->num = num;
	newNode->next = NULL;
bail:
	return newNode;
}

int is_list_empty(LIST *l)
{
	return (NULL == l);
}

int insert_data(LIST **head, int num)
{
    int nErr = 0;
    NODE *newNode = NULL;

    newNode = create_node(num);
    VERIFY(NULL != newNode);
    if (NULL == *head) {
        *head = newNode;
    }

bail:
    return nErr;
}

int remove_node(LIST *q)
{
	NODE *tmp = NULL;
        int num = 0;

	if (is_list_empty(q)) {
		printf ("list is empty\n");
		return 0;
	}

	tmp = q;
	q = q->next;
	printf ("dequeue node %d\n", tmp->num);
        num = tmp->num;
        free(tmp);
        return num;
}

void print_queue(LIST *q)
{
	NODE *tmpHead = q;

	while(tmpHead) {
		printf ("%d ", tmpHead->num);
		tmpHead = tmpHead->next;
	}
	printf ("\n");
}
