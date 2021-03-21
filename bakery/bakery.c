#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "event.h"
#include "customer.h"
#include "queue.h"
#include "prioqueue.h"

#define N_VENDORS 4
#define CLOSING_TIME 1500
#define ARRIVAL_RATE (1.0 / 60)
#define MEAN_SERVICE_TIME 150

prioqueue *event_queue;
queue *customer_queue;
customer *vendor[N_VENDORS];

int current_time;
double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}
void add_customer(customer *c)
{
    int i = 0;
    for (i = 0; i < N_VENDORS; i++)
    {
        if (vendor[i] == NULL)
        {
            vendor[i] = c;
            event *depart = create_departure(current_time + normal_delay(MEAN_SERVICE_TIME), c);
            insert_pq(event_queue, depart);
            return;
        }
        else if (i == N_VENDORS - 1 && vendor[i] != NULL)
        {
            enqueue_q(customer_queue, c);
        }
    }
}
void remove_customer(customer *c)
{
    int i;
    for (i = 0; i < N_VENDORS; i++)
    {
        if (vendor[i] == c)
        {
            vendor[i] = NULL;
            free_customer(c);
            if (size_q(customer_queue) != 0)
            {
                customer *c2 = dequeue_q(customer_queue);
                vendor[i] = c2;
                event *depart = create_departure(current_time + normal_delay(MEAN_SERVICE_TIME), c2);
                insert_pq(event_queue, depart);
            }
        }
    }
}
void process_arrival(event *e)
{
    add_customer(e->c);
    int time = current_time + normal_delay(1.0 / ARRIVAL_RATE);
    customer *newCustomer = create_customer(time);
    event *newEvent = create_arrival(time, newCustomer);
    insert_pq(event_queue, newEvent);
}

void process_departure(event *e)
{
    remove_customer(e->c);
}

void vision()
{
    int i;
    char str[] = "   ";
    char vend[] = "____";
    for (i = 0; i < N_VENDORS; i++)
    {
        if (vendor[i] != NULL)
        {
            vend[i] = 'X';
        }
    }
    for (i = 0; i < size_q(customer_queue); i++)
    {
        str[i] = 'X';
    }
    printf("%d | %s | %s", current_time, vend, str);
}
int main()
{

    /*init*/

    event_queue = create_pq();
    customer_queue = create_q();
    vendor[0] = NULL;
    vendor[1] = NULL;
    vendor[2] = NULL;

    customer *client1 = NULL;
    event *event1 = NULL;
    event *removedEvent = NULL;

    client1 = create_customer(60);
    event1 = create_arrival(client1->atime, client1);

    insert_pq(event_queue, event1);

    while (size_pq(event_queue) != 0)
    {

        if (current_time >= CLOSING_TIME)
        {
            break;
        }
        removedEvent = remove_min_pq(event_queue);
        current_time = removedEvent->etime;

        if (removedEvent->type == EVENT_ARRIVAL)
        {

            process_arrival(removedEvent);
        }
        else if (removedEvent->type == EVENT_DEPARTURE)
        {
            process_departure(removedEvent);
        }
        vision();
        free_event(removedEvent);
    }

    /* enqueue_q(customer_queue, client1);
  
    customer *clientAdded = dequeue_q(customer_queue);
    printf(" this the client %d ", clientAdded->atime);*/
    putchar('\n');

    return 0;
}