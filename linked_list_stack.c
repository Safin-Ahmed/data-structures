#include<stdio.h>
#include<stdlib.h>

// Structure of a linked list node
typedef struct node
{
    int data;
    struct node *next;
}
node;

// Structure of a stack
typedef struct stack
{
    node *top;
}
stack;

// Check if the stack is empty
int isEmpty(stack *s)
{
    if (!s->top)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Push a new element to the end of the stack
void push (stack *s, int val)
{
    // create new node
    node *n = malloc(sizeof(node));
    // Adding the data
    n->data = val;
    // Setting the next pointer to the current head
    n->next = s->top;
    // setting the new node as the new head of stack
    s->top = n;

}

// Remove the last element from the stack
void pop (stack *s)
{
    // Checking if the stack is empty
    if (isEmpty(s))
    {
        printf("Stack is empty!\n");
    }
    else
    {
        printf("Popped element = %d\n", s->top->data);
        // saving the current top element in a tmp variable
        node *tmp = s->top;
        // setting the next element as the top of the stack
        s->top = s->top->next;
        // Free the deleted element
        free(tmp);
    }

}

// Print all the elements of stack
void peek (stack *s)
{
    // Checking if the stack is empty
    if (isEmpty(s))
    {
        printf("The stack is empty!\n");
    }
    else
    {
        // storing the top node of the stack in tmp variable
        node *tmp = s->top;
        // loop until the tmp variable is not NULL
        while (tmp != NULL)
        {
            // print the data of current node
            printf("%d->", tmp->data);
            // update the tmp variable to the next node of current tmp node
            tmp = tmp->next;
        }
        // prints a newline
        printf("NULL\n");
    }
}

void destroyNode(node *n)
{
    if (n == NULL)
    {
        return;
    }
    else {
        destroyNode(n->next);
        free(n);
    }
}

void destroy(stack *s)
{   
    // Recursive call of destroy node to free nodes
    destroyNode(s->top);
    free(s);
}


int main()
{
    // dynamically allocate memory for a stack
    stack *s = malloc(sizeof(s));
    // assigning the top node to NULL
    s->top = NULL;
    // push 12 to the stack
    push(s, 12);
    // push 15 to the stack
    push(s, 15);
    // push 13 to the stack
    push(s, 13);
    // push 16 to the stack
    push(s, 16);
    // push 18 to the stack
    push(s, 18);
    // print the stack
    peek(s);
    if(isEmpty(s))
    {
        printf("The Stack is Empty!\n");
    }
    else
    {
        printf("The Stack is Not Empty!\n");
    }
    // Destroy the stack
    destroy(s);
    return 0;
}
