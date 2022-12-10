#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure for circular queue
typedef struct queue
{
    int size;
    int f;
    int r;
    int* arr;
}
queue;

// Checks if the queue is full
int isFull(queue *q)
{
    if (((q->r+1) % q->size) == q->f)
    {
        return 1;
    }
    return 0;
}

// Checks if the queue is empty
int isEmpty(queue *q)
{   
    if (q->r==q->f)
    {
        return 1;
    }
    return 0;
}

// Add item to the queue
void enqueue(queue *q, int val)
{
    if (isFull(q))
    {
        printf("This Queue is full!\n");
    }
    else
    {   
        
        q->r = (q->r + 1) % q->size;
        q->arr[q->r] = val;
        printf("Enqueued Element: %d\n", val);

    }
}

// Remove item from the queue
int dequeue (queue *q)
{
    int a = -1;
    if (isEmpty(q))
    {
        printf("This Queue is empty!");
    }
    else
    {
        q->f = (q->f + 1) % q->size;
        a = q->arr[q->f];
        printf("Dequeued Element: %d\n", a);
    }
    return a;
}

// Print the queue
void print (queue *q)
{   
    // Checks if the queue is empty or not
    if (isEmpty(q))
    {
        printf("This Queue is empty!");
    }
    else 
    {   
        // Loops through the Array
        for (int i = ((q->f + 1) % q->size); i <= q->r; i++)
        {
            printf("%d\n", q->arr[i]);
        }
    }
}

int main(int argc, char* argv[])
{   
    queue q;
    q.size = 4;
    q.f = q.r = 0;
    q.arr = (int*) malloc(q.size * sizeof(int));

    if(isEmpty(&q))
    {
        printf("Queue is Empty!\n");
    }

    // Enqueue few elements
    enqueue(&q, 12);
    enqueue(&q, 15);
    enqueue(&q, 16);

    // Print queue
    print(&q);

    // Dequeue
     dequeue(&q);
     dequeue(&q);
     dequeue(&q);

    // Enqueue 
    enqueue(&q, 19);
    enqueue(&q, 20);
    enqueue(&q, 21);


    // if empty
    if (isEmpty(&q))
    {
        printf("The Queue is Empty!\n");
    }

    // if full
    if (isFull(&q))
    {
        printf("The queue is full!\n");
    }

    print(&q);
    return 0;
}