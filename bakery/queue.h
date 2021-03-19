#ifndef QUEUE_H
#define QUEUE_H
#include "customer.h"

typedef struct _queue queue;

/**
 * Create and return a pointer to a new queue.
 */
queue *create_q();

/**
 * Free the memory associated with a queue.
 *
 * This function should be called on an empty queue.
 * It does not free the memory associated with items 
 * that remain in the queue.
 */
void free_q(queue *q);

/**
 * Return the current size of the queue.
 */
int size_q(queue *q);

/**
 * Add a customer to the end of the queue.
 */
void enqueue_q(queue *q, customer *c);

/**
 * Remove and a return a pointer to the first customer in the queue.
 */
customer *dequeue_q(queue *q);

#endif /* QUEUE_H */