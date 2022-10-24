
#include "queue.h"


void init_queue(Queue **q)
{
  *q=(Queue *)malloc(sizeof(Queue));
  (*q)->len=0;
  (*q)->tail=NULL;
  (*q)->head=NULL;
}



void free_queue(Queue** q)
{node *temp=NULL;

while((*q)->head)
{
  temp=(*q)->head;
  (*q)->head=(*q)->head->next;
  free(temp);
}
(*q)->len=0;
 (*q)->tail=(*q)->head=NULL;
}


int add_queue(Queue * q, void * val)
{node *nou=(node *)malloc(sizeof(node));
  if(nou==NULL)
    return 0;
  nou->data=val;
  nou->next=NULL;
  if(q->head==NULL)
  {
    q->head=q->tail=nou;
    q->len++;
  }
  else
  {
    q->tail->next=nou;
    q->tail=nou;
    q->len++;
  }
  return 1;
}


void* pop_queue(Queue *q)
{void* el;node *aux;
 el=q->head->data;
 if(q->head==q->tail)
 {
  free(q->head);
  q->head=q->tail=NULL;
 }
 else
 {
  aux=q->head;
  q->head=q->head->next;
  free(aux);
 }
 q->len--;
 return el;
}



void print_queue(Queue *q)
{node * current=q->head;
  while(current!=NULL)
  {
    printf(" %s ",(char *)current->data );
    current=current->next;
  }
  printf("\n");
}

void* front(Queue *q)
{
  return(q->head->data);
}


int isEmptyQueue(Queue *q)
{
  return q->len;
}