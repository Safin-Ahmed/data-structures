#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFUL)

typedef struct person {
    char name[MAX_NAME];
    int age;
    struct person * next;
}
person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name);
void init_hash_table();
void print_table();
bool insert(char *name, int age);
person * find(char *name);
person * delete(char *name);
void destroyList();
void destroy();

int main ()
{
    init_hash_table();
    insert("Safin", 24);
    insert("Mew", 12);
    insert("Sayeba", 3);
    print_table();
    person * tmp = find("Safin");
    if (tmp == NULL)
    {
        printf("Not Found\n");
    }
    else 
    {
        printf("Found user: %s\n", tmp->name);
    }

    destroy();
    print_table();

    


    return 0;
}

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

void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

void print_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t ", i);
            person *tmp = hash_table[i];
            while(tmp != NULL)
            {
                printf("%s - ", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }

    printf("End\n");
}

bool insert (char *name, int age)
{
    if (name == NULL) return false;
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        printf("Memory Insufficient!\n");
        return false;
    }
    strcpy(p->name, name);
    p->age = age;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

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
        person *final = tmp->next;
        free(hash_table[index]);
        hash_table[index] = final;
    }
    else
    {
        prev->next = tmp->next;
        free(tmp);
    }

    return tmp;
}

void destroyList(person *p)
{
    if (p == NULL)
    {
        return;
    }

    destroyList(p->next);
    free(p);
}

void destroy() {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash_table[i] == NULL)
        {
            continue;
        }
        else {
            destroyList(hash_table[i]);
        }
        
        hash_table[i] = NULL;
    }
}

/* 


*/