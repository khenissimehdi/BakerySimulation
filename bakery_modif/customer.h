#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
	int atime;	/* arrival time */
} customer;

/**
 * Create and return a pointer to a new customer.
 * atime: arrival time
 */
customer *create_customer(int atime);

/**
 * Free the memory associated with a customer.
 */
void free_customer(customer *c);

#endif /* CUSTOMER_H */