#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "prioqueue.h"
#include "event.h"

#define MAX_QUEUE_SIZE 100

typedef struct _link
{
    event *e;
    struct _link *next;

} link;

struct _prioqueue
{
    link *first;
    int size;
};

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
    event *cell;

    do
    {
        cell = remove_min_pq(q);

        free(cell);
    } while (cell->c != NULL && !is_Empty(q));

    free(q);
}

int size_pq(prioqueue *q)
{
    return q->size;
}

void insert_pq(prioqueue *q, event *e)
{
    link *current = q->first;
    link *new_lnk = (link *)malloc(sizeof(link));
    new_lnk->e = e;

    if (q->first == NULL)
    {
        q->first = new_lnk;
        q->size++;
        return;
    }
    else if (e->etime < q->first->e->etime)
    {
        new_lnk->next = q->first;
        q->first = new_lnk;
        q->size++;
        return;
    }

    while (current->e->etime > e->etime)
    {
        current = current->next;
    }
    new_lnk->next = current->next;
    current->next = new_lnk;
    q->size++;
}

event *remove_min_pq(prioqueue *q)
{
    assert(q->size > 0);
    link *tmp = q->first;
    event *e = q->first->e;
    q->first = q->first->next;
    q->size--;
    free(tmp);
    return e;
}
void display_pq(prioqueue *q)
{
    link *current = q->first;
    while (current != NULL)
    {
        printf("  %d \n", current->e->c->atime);
        current = current->next;
    }
}