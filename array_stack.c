#include <stdio.h>
#include <stdlib.h>
typedef struct stack 
{
    int size;
    int top;
    int * arr;
}
stack;

int isEmpty(stack *s)
{
    if(s->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFull(stack *s)
{
    if(s->top == s->size - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(stack *s, int val)
{
    if (isFull(s))
    {
        printf("Stack Overflow!\n");
    }
    else
    {
        s->top++;
        s->arr[s->top] = val;
    }
}

void pop(stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack Underflow!\n");
    }
    else
    {
        s->top--;
    }
}

void peek(stack *s)
{
    for (int i = s->top; i >= 0; i--)
    {
        printf("%d\n", s->arr[i]);
    }
    if(s->top == -1)
    {
        printf("Stack is empty!");
    }
}

void destroy(stack *s)
{
    free(s->arr);
    free(s);
}

int main()
{   stack *s = (stack *) malloc(sizeof(stack));
    s->size = 5;
    s->top = -1;
    s->arr = (int *) malloc(s->size * sizeof(int));
    printf("Stack has been created successfully\n");

    // Check if stack is empty
    if (isEmpty(s))
    {
        printf("The stack is empty!\n");
    }
    else 
    {
        printf("The stack is not empty!\n");
    }

    push(s, 56);
    push(s, 57);
    push(s, 58);
    push(s, 59);
    push(s, 60);
    pop(s);
    push(s, 54);
    // Check if stack is empty
    if (isEmpty(s))
    {
        printf("The stack is empty!\n");
    }
    else 
    {
        printf("The stack is not empty!\n");
    }

    // Display the stack
    peek(s);

    // Destroy the stack
    destroy(s);
    return 0;
}