#include <stdlib.h>
#include <assert.h>
#include "prioqueue.h"
#include "event.h"

#define MAX_QUEUE_SIZE 100

struct _prioqueue {
    event* tab[MAX_QUEUE_SIZE];
    int    size;
};

prioqueue *create_pq() {
    prioqueue *q = (prioqueue*)malloc(sizeof(prioqueue));
    q->size = 0;
    return q;
}

void free_pq(prioqueue *q) {
    free(q);
}

int size_pq(prioqueue *q) {
    return q->size;
}

void insert_pq(prioqueue *q, event *e) {
    assert(q->size < MAX_QUEUE_SIZE);
    int i = q->size;
    while (i > 0 && q->tab[i-1]->etime < e->etime) {
        q->tab[i] = q->tab[i-1];
        i--;
    }
    q->tab[i] = e;
    q->size++;
}

event *remove_min_pq(prioqueue *q) {
    assert(q->size > 0);
    q->size--;
    event *e = q->tab[q->size];
    return e;
}
