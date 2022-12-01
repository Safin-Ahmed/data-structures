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
bool find(node *list, int number);
node * insert(node *list, int number);
void destroy(node *list); 

int main()
{   
    // List of size 0
    node *list = NULL;

    // Add a number to list
    node *n = malloc(sizeof(node));
    if(n == NULL)
    {
        return 1;
    }

    n->number = 1;
    n->next = NULL;

    // update list to point new node
    list = n;

    // Add a number to list
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;

    // Add a number to list
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 1;
    n->next = NULL;
    list->next->next = n;

    // Print Numbers
    for(node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    // Free list
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    return 0;
}

node * create(int number) 
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = number;
    n->next = NULL;

    return n;
}

bool find(node *list, int number)
{
    node *trav = list;
    while(trav != NULL)
    {   
        if (trav->number == number)
        {
            return true; 
        }

        else if(trav->number != number)
        {
            trav = list->next;
        }
    }

    if (trav == NULL)
    {
        return false;
    }

}

node * insert(node *list, int number)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    n->number = number;
    n->next = list;
    list = n;

    return list;
}

void destroy(node *list)
{
    if(list == NULL)
    {
        return;
    }

    destroy(list->next);
    free(list);
}
