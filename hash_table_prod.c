#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*) (0xFFFFFFFFFFFFUL)

typedef struct {
    char name[MAX_NAME];
    int age;
}
person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name);

void init_hash_table();
void print_table();
bool insert(person *p);
person * find(char *name);
person * delete (char *name);


int main()
{   
    init_hash_table();
    person safin = {.name = "Safin Ahmed", .age = 22};
    person enayet = {.name = "Enayet Hasan", .age = 23};
    person john = {.name = "John Hasan", .age = 23};

    insert(&safin);
    insert(&enayet);
    insert(&john);

    print_table(); 
    person *tmp = find("Safin");
    if(tmp == NULL)
    {
        printf("Not Found\n");
    }
    else
    {
        printf("Found Person\n");
    }

    delete("John Hasan");
    print_table();
    return 0;
}

unsigned int hash(char *name)
{
    int length = strlen(name);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }

    return hash_value;

}

void init_hash_table()
{
    for(int i = 0; i < TABLE_SIZE; i++)
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
        else if (hash_table[i] == DELETED_NODE)
        {
            printf("\t%i\t------<deleted>\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
}

bool insert(person *p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (i + index) % TABLE_SIZE;

        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE)
        {
            hash_table[try] = p;
            return true;
        }
    }

    return false;
}

person * find(char *name)
{
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;

        if (hash_table[try] == NULL)
        {
            return false;
        }

        if (hash_table[try] == DELETED_NODE)
        {
            continue; 
        }

        if (strcmp(hash_table[try]->name, name) == 0)
        {
            return hash_table[try];
        }
    }

    return NULL;
}

person * delete (char *name) 
{
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL)
        {
            return NULL;
        }
        else if (hash_table[try] == DELETED_NODE)
        {
            continue;
        }
        else if (strcmp(hash_table[try]->name, name) == 0)
        {
            person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }

    return NULL;
}

