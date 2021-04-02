#ifndef EVENT_H
#define EVENT_H
#include "customer.h"

typedef enum {
    EVENT_ARRIVAL,
    EVENT_DEPARTURE
} event_t;

typedef struct {
    event_t     type;   /* event type */
    int         etime;  /* event time */
    customer    *c;     /* customer pointer  */
} event;

/**
 * Create and return a pointer to a new arrival event.
 * etime: event time
 * c: arriving customer
 */
event *create_arrival(int etime, customer *c);

/**
 * Create and return a pointer to a new departure event.
 * etime: event time
 * c: departing customer
 */
event *create_departure(int etime, customer *c);

/**
 * Free the memory associated with an event.
 */
void free_event(event *e);

#endif /* EVENT_H */