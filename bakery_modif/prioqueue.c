#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "prioqueue.h"
#include "event.h"

#define MAX_QUEUE_SIZE 100

prioqueue *create_pq()
{
    prioqueue *q = (prioqueue *)malloc(sizeof(prioqueue));
    q->first = NULL;
    q->size = 0;
    return q;
}
int is_Empty(prioqueue *prioqueue)
{

    if (prioqueue->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void free_pq(prioqueue *q)
{
    free(q);
}

int size_pq(prioqueue *q)
{
    return q->size;
}

void insert_pq(prioqueue *q, event *e)
{
    link *current = NULL;

    link *new_lnk = (link *)malloc(sizeof(link));
    new_lnk->e = e;
    new_lnk->next = NULL;

    if (q->first == NULL)
    {
        q->first = new_lnk;

        q->size++;
        return;
    }

    if (new_lnk->e->etime < q->first->e->etime)
    {
        new_lnk->next = q->first;
        q->first = new_lnk;
        q->size++;
        return;
    }
    current = q->first;

    while (current->next != NULL && current->next->e->etime < new_lnk->e->etime)
    {

        current = current->next;
    }

    new_lnk->next = current->next;
    current->next = new_lnk;
    q->size++;
}

event *remove_min_pq(prioqueue *q)
{
    if (q->size > 0)
    {
        link *tmp = q->first;
        event *e = q->first->e;
        q->first = q->first->next;
        q->size--;
        free(tmp);
        return e;
    }
    return NULL;
}
void display_pq(prioqueue *q)
{
    link *current = q->first;
    while (current != NULL)
    {
        printf("  %d \n", current->e->etime);
        current = current->next;
    }
}