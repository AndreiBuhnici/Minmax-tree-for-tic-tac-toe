#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	void * data;
	struct node* next;
}node;

 
typedef struct Queue{
	struct node *tail , *head;
	int len;
}Queue;


void init_queue(Queue **q);
void free_queue(Queue** q);
int add_queue(Queue * q, void * val);
void* pop_queue(Queue *q);
void print_queue(Queue *q);
void* front(Queue *q);
int isEmptyQueue(Queue *q);
#endif