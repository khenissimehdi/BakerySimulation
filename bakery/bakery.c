#include <stdio.h>
#include "event.h"
#include "customer.h"
#include "queue.h"
#include "prioqueue.h"

#define N_VENDORS 3

prioqueue*  event_queue;
queue*      customer_queue;
customer*   vendor[N_VENDORS];

void process_arrival(event *e) {
}

void process_departure(event *e) {
}

int main() {

    return 0;
}