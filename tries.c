#include <stdio.h>
#include <stdlib.h>

// Define the character size
#define CHAR_SIZE 26

// Data structure to store a trie Node
typedef struct Trie
{
    int isLeaf;
    struct Trie *character[CHAR_SIZE];
}
Trie;

// Function that returns a new Trie Node
Trie * getNewTrieNode()
{
    Trie *node = malloc(sizeof(Trie));
    node->isLeaf = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }

    return node;
}

// Insert a string into Trie
void insert(Trie *head, char *str)
{
    Trie *cur = head;
    while(*str)
    {
        // Create a new node if the path does not exist
        if (cur->character[*str - 'a'] == NULL)
        {
            cur->character[*str - 'a'] = getNewTrieNode();
        }

        // Go to the next node
        cur = cur->character[*str - 'a'];

        // Move to the next character
        str++;
    }

    // Mark the current node as leaf
    cur->isLeaf = 1;
}

// Search a string
int search(Trie *head, char *str)
{
    // return 0 if trie is empty
    if (head == NULL)
    {
        return 2;
    }

    Trie *cur = head; 
    while(*str)
    {
        // go to the next node
        cur = cur->character[*str - 'a'];

        // if it's the end of path or invalid in Trie
        if (cur == NULL)
        {
            return 0;
        }

        str++;
    }

    // returns if the current node is leaf and reached the end of string
    return cur->isLeaf;
}

// Check if the given node has any children
int hasChildren(Trie *node)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (node->character[i])
        {
            return 1; // child found
        }
    }

    return 0;
}

// Recursive Function to delete a string from Trie
int delete (struct Trie **cur, char *str)
{
    // return 0 if Trie is empty
    if (*cur == NULL)
    {
        return 0;
    }
    
    // if the end of string is not reached
    if (*str)
    {   
        if (*cur != NULL && (*cur)->character[*str - 'a'] != NULL && delete(&((*cur)->character[*str - 'a']), str + 1) && (*cur)->isLeaf == 0)
        {
            if (!hasChildren(*cur))
            {
                free(*cur);
                *cur = NULL;
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }

    // If the end of string is reached
    if (*str == '\0' && (*cur)->isLeaf)
    {
        if (!hasChildren(*cur))
        {
            free (*cur);
            (*cur) = NULL;
            return 1;
        }
        else
        {   
            // Mark the node as non leaf node (Dont' DELETE)
            (*cur)->isLeaf = 0;
            return 0;
        }
    }

    return 0;
}

void printTries(Trie *node)
{
    if(node == NULL)
    {
        return 0;
    }
}

int main()
{   
    Trie *head = getNewTrieNode();
    insert(head, "hello");
    printf("Find hello %d ", search(head, "hello"));

    insert(head, "safin");
    printf("Find safin %d ", search(head, "safin"));

    printf("Find safins %d ", search(head, "safins"));

    insert(head, "hell");
    printf("Find hell: %d ", search(head, "hell"));

    insert(head, "ahmed");
    printf("Find ahmed: %d \n", search(head, "ahmed"));

    delete(&head, "ahmed");
    printf("Find ahmed: %d \n", search(head, "ahmed"));
    return 0;
}