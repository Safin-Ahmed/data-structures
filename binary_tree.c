#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Represents a node
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void free_tree(node *root);
node * find_successor(node *root);
node * delete(node *root, int number);
node * create(int number);
node * insert(node *root, int number);
void print_tree(node *root);
bool search(node *tree, int number);

int main (void)
{   
    // Tree of size 0
    node *tree = create(2);

    // Add number to list
    insert(tree, 3);
    insert(tree, 1);
    insert(tree, 4);
    insert(tree, 6);
    insert(tree, 5);
    delete(tree, 4);

    print_tree(tree);
    free_tree(tree);
}

node * create(int number) 
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    n->number = number;
    n->left = NULL;
    n->right = NULL;

    return n;
}

node * insert(node *root, int number)
{
    if (root == NULL)
    {
       return create(number);
    }

    else if (number < root->number)
    {
        root->left = insert(root->left, number); 
    }

    else if (number > root->number)
    {
        root->right = insert(root->right, number);
    }

    return root;
    
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return; 
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}
bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false; 
    }

    else if (number < tree->number)
    {
        return search(tree->left, number);
    }

    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else
    {
        return true;
    }
}

node * find_successor(node *root)
{
    node *current = root;

    // Find the leftmost leaf
    while (current && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

node * delete(node *root, int number)
{   
    // Return if tree is empty
    if (root == NULL)
    {
        return root;
    }

    // Find the node to be deleted
    if (number < root->number)
    {
        root->left = delete(root->left, number);
    }
    else if (number > root->number)
    {
        root->right = delete(root->right, number);
    }
    else 
    {
        // If the node is with only one child or no child
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp; 
        }

        // If the node has two children
        struct node *temp = find_successor(root->right);
        root->number = temp->number;

        // Delete the successor
        root->right = delete(root->right, temp->number);
    }

    return root;

}