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
    unsigned char newprefix[length + 2];
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

int main()
{   
    trienode * root = NULL;
    insert(&root, "KIT");
    insert(&root, "CATTLE");
    insert(&root, "CAT");
    insert(&root, "HAPPY");

    print(root);
    return 0;
}