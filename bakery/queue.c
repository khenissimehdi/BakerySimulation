#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "customer.h"

#define MAX_QUEUE_SIZE 100

struct _queue {
    customer* tab[MAX_QUEUE_SIZE];
    int       first;
    int       size;
};

queue *create_q() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = 0;
    q->size = 0;
    return q;
}

void free_q(queue *q) {
    free(q);
}

int size_q(queue *q) {
    return q->size;
}

void enqueue_q(queue *q, customer *c) {
    assert(q->size < MAX_QUEUE_SIZE);
    q->tab[(q->first+q->size) % MAX_QUEUE_SIZE] = c;
    q->size++;
}

customer *dequeue_q(queue *q) {
    assert(q->size > 0);
    customer *c = q->tab[q->first];
    q->first = (q->first+1) % MAX_QUEUE_SIZE;
    q->size--;
    return c;
}
