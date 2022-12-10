#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of QUEUE_EMPTY
#define QUEUE_EMPTY 1

// Structure of a linked list node
typedef struct node {
    int value;
    struct node *next;
}
node;

// Structure of a Queue
typedef struct {
    node *head;
    node *tail;
}
queue;

// Initialize Queue
void init_queue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

// Enqueue -> Add item to the queue
bool enqueue(queue *q, int value)
{   
    // create a new node
    node * newnode = malloc(sizeof(node));
    if (newnode == NULL) return false;
    newnode->value = value;
    newnode->next = NULL;

    // if there is a tail, connect that tail to this new node 
    if(q->tail != NULL)
    {
        q->tail->next = newnode;
    }
    q->tail = newnode;
    // make sure the head makes sense
    if (q->head == NULL)
    {
        q->head = newnode;
    }

    return true;
}

// Dequeue -> Remove item from the queue
int dequeue (queue *q)
{   
    // Check to see if the queue is empty.
    if (q->head == NULL) return QUEUE_EMPTY;

    // save the head of the queue
    node *tmp = q->head;
    
    // save the result
    int result = tmp->value;

    // take it off
    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    free(tmp);
    return result;
}

// Print Queue -> Print all items of the queue
void print (queue *q)
{
    // Check to see if the queue is empty.
    if (q->head == NULL)
    {
        printf("The Queue is Empty!");
    }
    else 
    {
        // Create a traverse pointer
        node *trav = q->head;
        while(trav != NULL)
        {
            printf("%d\n", trav->value);
            trav = trav->next;
        }
    }

    
}

int main()
{
    queue q1, q2, q3;
    init_queue(&q1);
    init_queue(&q2);
    init_queue(&q3);

    enqueue(&q1, 12);
    enqueue(&q1, 13);
    enqueue(&q1, 14);

    // Print all elements of q1 queue.
    print(&q1);

    // Removes 12 from the q1 queue.
    dequeue(&q1);
    // Print all elements of q1 queue.
    print(&q1);
}