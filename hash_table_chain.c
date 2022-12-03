#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFUL)

typedef struct person {
    char name[MAX_NAME];
    int age;
    struct person * next
}
person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{   
    int length = strlen(name);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }

    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    // Table is empty
}

void print_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else {
            printf("\t%i\t ", i);
            person *tmp = hash_table[i];
            while (tmp != NULL)
            {
                printf("%s - ", hash_table[i]->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }

    printf("End\n");
}

bool insert(person *p) 
{
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

// find a person in the table by their name
person * find(char *name)
{
    int index = hash(name);
    person *tmp = hash_table[index];
    while(tmp != NULL && strcmp(tmp->name, name) != 0)
    {
        tmp = tmp->next;
    }
    return tmp;
}

person * delete (char *name)
{
    int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while(tmp != NULL && strcmp(tmp->name, name) != 0)
    {   
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        return NULL;
    }
    if (prev == NULL) 
    {
        // deleting the head
        hash_table[index] = tmp->next;
    }
    else {
        prev->next = tmp->next;
    }
    return tmp;
}

int main()
{   
    init_hash_table();
     
    person safin = {.name = "Safin", .age = 22};
    person kate = {.name = "Kate", .age = 24};
    person jane = {.name = "Jane", .age = 24};
    person rupa = {.name = "Rupa", .age = 24};
    person parthib = {.name = "Parthib", .age = 24};

    insert(&safin);
    insert(&kate);
    insert(&jane);
    insert(&rupa);
    insert(&parthib);
    print_table();

    person *tmp = find("Mpho");
    if (tmp == NULL)
    {
        printf("Not found\n");
    }
    else 
    {
        printf("Found %s\n", tmp->name);
    }

    person *del = delete("Safin");
    printf("del: %p\n", del);
    print_table();

    tmp = find("Safin");
    if (tmp == NULL)
    {
        printf("Not found\n");
    }
    else 
    {
        printf("Found %s\n", tmp->name);
    }
    return 0;
}