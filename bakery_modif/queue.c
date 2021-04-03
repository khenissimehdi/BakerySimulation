#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"
#include "customer.h"

#define MAX_QUEUE_SIZE 100

typedef struct _link
{
    customer *c;
    struct _link *next;
} link;

struct _queue
{
    link *first;
    link *last;
    int size;
};

queue *create_q()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}

int isEmpty(queue *queue)
{

    if (queue->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void free_q(queue *q)
{

    customer *cell;
    do
    {
        cell = dequeue_q(q);

        free(cell);
    } while (cell != NULL && !isEmpty(q));

    free(q);

    
}

int size_q(queue *q)
{

    return q->size;
}

void enqueue_q(queue *q, customer *c)
{
    link *new_lnk = (link *)malloc(sizeof(link));
    new_lnk->c = c;
    new_lnk->next = NULL;
    if (q->last != NULL)
    {
        q->last->next = new_lnk;
    }
    else
    {

        q->first = new_lnk;
    }
    q->last = new_lnk;
    q->size++;
}

customer *dequeue_q(queue *q)
{
    if(q->size > 0){
         link *tmp = q->first;
        customer *c = q->first->c;
        q->first = q->first->next;

        q->size--;

        free(tmp);
        if (q->first == NULL)
        {
            q->last = NULL;
        }
        return c;

    }
    return NULL;
   
}
void display_q(queue *q)
{
    link *current = q->first;
    while (current != NULL)
    {
        printf("  %d \n", current->c->atime);
        current = current->next;
    }
}
