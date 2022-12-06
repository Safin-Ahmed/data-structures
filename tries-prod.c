#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CHARS 256

typedef struct trienode
{
    struct trienode *children[NUM_CHARS];
    bool terminal;
}
trienode;

trienode *create()
{
    trienode *n = malloc(sizeof(trienode));
    for (int i = 0; i < NUM_CHARS; i++)
    {
        n->children[i] = NULL;
    }
    n->terminal = false;
    return n;
}

bool insert(trienode **root, char *signedtext)
{
    if (*root == NULL)
    {
        *root = create();
    }

    unsigned char *text = (unsigned char *)signedtext;
    trienode *tmp = *root;
    int length = strlen(signedtext);
    for (int i = 0; i < length; i++)
    {
        if (tmp->children[text[i]] == NULL)
        {
            // create a new node
            tmp->children[text[i]] = create();
        }

        tmp = tmp->children[text[i]];
    }

    if (tmp->terminal)
    {
        return false;
    }
    else
    {
        tmp->terminal = true;
        return true;
    }
}

void print_rec(trienode *node, unsigned char *prefix, int length)
{
    unsigned char *newprefix = malloc(length + 2);
    memcpy(newprefix, prefix, length);

    newprefix[length + 1] = 0;

    if (node->terminal)
    {
        printf("WORD: %s\n", prefix);
    }

    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (node->children[i] != NULL)
        {
            newprefix[length] = i;
            print_rec(node->children[i], newprefix, length + 1);
        }
    }

    free(newprefix);
}

void print(trienode * root)
{
    if (root == NULL)
    {
        printf("TRIE EMPTY!\n");
        return;
    }

    print_rec(root, NULL, 0);
}

// Search a String
bool search(trienode *head, char* str)
{
    // return 0 if trie is empty
    if (head == NULL)
    {
        return false;
    }

    trienode *cur = head;
    while(*str)
    {
        // go to the next node
        cur = cur->children[(unsigned char)(*str)];

        // If it's an invalid path return NULL
        if (cur == NULL)
        {
            return 0;
        }

        str++;
    }

    return cur->terminal;
}

// Detect if the current node has children
int hasChildren(trienode *node)
{
    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (node->children[i])
        {
            // The node has children
            return 1;
        }
    }

    return 0;
}

// Recursive Function to delete a string from Trie
int delete (trienode **cur, char *str)
{
    // Return 0 if trie is empty
    if (*cur == NULL)
    {
        return 0;
    }

    // If the end of string is not reached
    if (*str)
    {
        if (*cur != NULL && (*cur)->children[(unsigned char)*str] != NULL && delete(&(*cur)->children[(unsigned char)*str], str + 1) && (*cur)->terminal == false)
        {
            if (!hasChildren(*cur))
            {
                *cur = NULL;
                free(*cur);
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }

    // If the end of string is reached
    if (*str == '\0' && (*cur)->terminal)
    {
        if (!hasChildren(*cur))
        {
            (*cur) = NULL;
            free(*cur);
            return 1;
        }
        else
        {
            // Mark the node as non leaf node (DON'T DELETE)
            (*cur)->terminal = false;
            return 0;
        }
    }

    return 0;
}

void destroy(trienode **root)
{
    if ((*root) != NULL)
    {
        for (int i = 0; i < NUM_CHARS; i++)
        {
            if ((*root)->children[i] != NULL)
            {
                destroy(&((*root)->children[i]));
            }
        }
        free(*root);
    }
}

int main()
{
    trienode * root = NULL;
    insert(&root, "KIT");
    // insert(&root, "CATTLE");
    // insert(&root, "CAT");
    // insert(&root, "HAPPY");
    // delete(&root, "CAT");
    print(root);

    bool tmp = search(root, "CATTLE");
    if (tmp != false)
    {
        printf("Found Word\n");
    }
    else
    {
        printf("Not Found Word\n");
    }

    destroy(&root);


    return 0;
}