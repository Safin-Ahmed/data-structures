#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
    int number;
    struct node *next;
    struct node *prev;
}
node;

node * create(int number);
node * find(node *list, int number);
node * insert(node **list, int number);
node * push(node **list, int number);
void destroy(node *list);
void delete(node **list, node *target);
void print(node *list);

int main()
{
    node *list = create(12);
    insert(&list, 13);
    insert(&list, 14);
    print(list);

   node *element = find(list, 14);
   delete(&list, element);
    print(list);


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
    n->prev = NULL;

    return n;
}

node * insert(node **list, int number)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    n->number = number;
    n->next = *list;
    n->prev = NULL;
    (*list)->prev = n;
    *list = n;

    return *list;
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

void print(node *list)
{

    if(list == NULL)
    {
        return;
    }

    for(node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);

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

void delete(node **list, node *target)
{
    if (*list == NULL || target == NULL)
    {
        return;
    }
    // If head is the target
    if (*list == target)
    {
        *list = target->next;
    }

    // Change next only if target is not the last node
    if (target->next != NULL)
    {
        target->next->prev = target->prev;
    }

    // Change prev only if target is not the first node
    if (target->prev != NULL)
    {
        target->prev->next = target->next;
    }

    // Free the target
    free(target);
}