#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "event.h"
#include "customer.h"
#include "queue.h"
#include "prioqueue.h"

#define N_VENDORS 3
#define CLOSING_TIME 400
#define ARRIVAL_RATE (1.0 / 60)
#define MEAN_SERVICE_TIME 200

prioqueue *event_queue;
queue *customer_queue;
customer *vendor[N_VENDORS];
int number_served_clients = 0;
int total_time = 0;
int mean_time = 0;
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
           
       
               
              

            
                event *depart = create_departure(current_time + (int)normal_delay(MEAN_SERVICE_TIME), c);
                
                insert_pq(event_queue, depart);
                
                
            
            return;
        }
     
    }
     enqueue_q(customer_queue, c);
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
                event *depart = create_departure(current_time +(int) normal_delay(MEAN_SERVICE_TIME), c2);
              
                
                insert_pq(event_queue, depart);
                
                
            }
        }
    }
}
void process_arrival(event *e)
{
    
    add_customer(e->c);

    int time = current_time + (int) normal_delay(1.0 / ARRIVAL_RATE);
      printf("%d \n", time);
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

    printf("%d | ", current_time);
    for (i = 0; i < N_VENDORS; i++)
    {
        if (vendor[i] != NULL)
        {
            putchar('X');
        }
        else
        {
            putchar('_');
        }
    }
    printf(" | ");
    for (i = 0; i < size_q(customer_queue); i++)
    {
        putchar('X');
    }

    putchar('\n');
}
void init_vendors()
{
    size_t i;
    for (i = 0; i < N_VENDORS; i++)
    {
        vendor[i] = NULL;
    }
}




int main()
{

    event_queue = create_pq();
    customer_queue = create_q();
    init_vendors();

    customer *client1 = NULL;
    event *event1 = NULL;
    event *removedEvent = NULL;

    client1 = create_customer(60);
    event1 = create_arrival(client1->atime, client1);


    insert_pq(event_queue, event1);

    while (size_pq(event_queue) != 0)
    {
        

        removedEvent = remove_min_pq(event_queue);
       
        current_time = removedEvent->etime;
         
    
        

       if (current_time >= CLOSING_TIME)
        {
            if (removedEvent->type == EVENT_DEPARTURE)
            {
              
                process_departure(removedEvent);
            }
            else
            {
                free_customer(removedEvent->c);
            }
            
        }

        if (current_time <= CLOSING_TIME && removedEvent->type == EVENT_ARRIVAL)
        {
            process_arrival(removedEvent);
        }
        else if (current_time <= CLOSING_TIME && removedEvent->type == EVENT_DEPARTURE)
        {
            number_served_clients += 1;
            total_time += (current_time - removedEvent->c->atime);
            process_departure(removedEvent);
        }
       
        
     /* display_pq(event_queue);*/
      vision();
        free_event(removedEvent);
       

       

    }
    mean_time = total_time / number_served_clients;
    printf(" Served clients : %d \n", number_served_clients);

    printf(" Mean clients time : %d \n", mean_time);
    printf(" size customer queue : %d \n", size_q(customer_queue));
   
    free_q(customer_queue);
    free_pq(event_queue);
     /*if (event_queue != NULL)
    {
       printf("   yes %d",event_queue->size);
    }*/
    
  
    

    putchar('\n');
    return 0;
}