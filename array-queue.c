#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct queue
{
    int size;
    int f;
    int r;
    int* arr;
}
queue;

int isFull(queue *q)
{
    if (q->r==q->size-1)
    {
        return 1;
    }
    return 0;
}

int isEmpty(queue *q)
{
    if (q->r==q->f)
    {
        return 1;
    }
    return 0;
}

void enqueue(queue *q, int val)
{
    if (isFull(q))
    {
        printf("This Queue is full!");
    }
    else
    {
        q->r++;
        q->arr[q->r] = val;

    }
}

int dequeue (queue *q)
{
    int a = -1;
    if (isEmpty(q))
    {
        printf("This Queue is empty!");
    }
    else
    {
        q->f++;
        a = q->arr[q->f];
    }
    return a;
}

int main(int argc, char* argv[])
{   
    queue q;
    q.size = 100;
    q.f = q.r = -1;
    q.arr = (int*) malloc(q.size * sizeof(int));

    if(isEmpty(&q))
    {
        printf("Queue is Empty!\n");
    }

    // Enqueue few elements
    enqueue(&q, 12);
    enqueue(&q, 15);

    printf("Dequeuing Element %d\n", dequeue(&q));
    printf("Dequeuing Element %d\n", dequeue(&q));
    return 0;
}