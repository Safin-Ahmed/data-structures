#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

node * create(int number);
node * find(node *list, int number);
node * insert(node **list, int number);
node * push(node **list, int number);
void destroy(node *list);
void print(node *list);

int main()
{
    // Create List
    node *list = create(2);
    printf("Init Pointer: %p\n", list);

    // Insert a Number
    insert(&list, 12);
    insert(&list, 21);
    insert(&list, 22);
    push(&list, 23);
    printf("List Pointer: %p\n", list);

    // Print Linkedlist
    print(list);

    // Destroy Linkedlist
    destroy(list);
    return 0;
}

node * create(int number)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    n->number = number;
    n->next = NULL;

    return n;
}

node * find(node *list, int number)
{
    if (list == NULL)
    {
        return NULL;
    }

    else if (list->number != number)
    {
        return find(list->next, number);
    }
    else
    {
        return list;
    }

}

node * insert(node **list, int number)
{

    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("NULL MEM!\n");
        destroy(*list);
        return NULL;
    }

    n->number = number;
    n->next = *list;
    *list = n;

    printf("After inserting: %p\n", *list);


    return *list;
}

void destroy(node *list)
{
    printf("Destory Input Pointer: %p\n", list);
    if(list == NULL)
    {
        return;
    }

    destroy(list->next);
    free(list);
}

void print(node *list)
{

    if(list == NULL)
    {
        return;
    }

    for(node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
        printf("%p\n", tmp->next);
    }
}

node * push(node **list, int number)
{
    if(*list == NULL)
    {
        return NULL;
    }

    node *n = malloc(sizeof(node));
    n->number = number;
    n->next = NULL;

    node *last_element = *list;
    while (last_element->next != NULL)
    {
        last_element = last_element->next;
    }

    last_element->next = n;

    return n;
}