
#include "FuncToTable.h"
#include "HashTable.h"

// Ht_item *CreateItem(char *key, char *value)
// {
//     Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
//     item->key = (char *)malloc(strlen(key) + 1);
//     item->value = (char *)mlloc(strlen(value) + 1);

//     strcpy(item->key, key);
//     strcpy(item->value, value);

//     return item;
// }
char *Search(HashTable *table, char *key)
{
    int index = HashKey(key, table->size);
    Ht_item *item = table->items[index];
    LinkedList *head = table->overflow_buckets[index];
    while (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
            return item->value;
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}

void Insert(HashTable *table, char *key, char *value)
{
    Ht_item *item = CreateItem(key, value);
    int index = HashKey(key, table->size);
    Ht_item *current_item = table->items[index];

    if (current_item == NULL)
    {
        if (table->count == table->size)
        {
            printf("Insert Error: Hash Table is full\n");
            return;
        }
        // printf("item")
        table->items[index] = item;
        table->count++;
    }

    else
    {
        if (strcmp(current_item->key, key) == 0)
        {
            strcpy(table->items[index]->value, value);
            return;
        }
        else
        {
            HandleCollision(table, index, item);
            return;
        }
    }
}
void PrintTable(HashTable *table)
{
    printf("\nHash Table\n");
    Space();
    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf(RED "Index:" GREEN " %d," RED "Key:" GREEN " %s," RED " Value:" GREEN " %s\n" RESET, i, table->items[i]->key, table->items[i]->value);
            if (table->overflow_buckets[i])
            {
                LinkedList *test;
                test = table->overflow_buckets[i];
                while (test)
                {
                    printf(RED "Index:" PURPLE " %d," RED " Key:" PURPLE " %s," RED " Value:" PURPLE "%s\n" RESET, i, test->item->key, test->item->value);
                    test = test->next;
                }
            }
        }
    }
    Space();
}
void PrintSearch(HashTable *table, char *key, int size)
{
    char *val;
    if ((val = Search(table, key)) == NULL)
    {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else
    {
        int index = HashKey(key, size);
        printf("Index:%d, Key:%s, Value:%s\n", index, key, val);
    }
}
void Delete(HashTable *table, char *key)
{
    int index = HashKey(key, table->size);
    Ht_item *item = table->items[index];
    LinkedList *head = table->overflow_buckets[index];
    if (item == NULL)
    {
        return;
    }
    else
    {
        if (head == NULL && strcmp(item->key, key) == 0)
        {
            table->items[index] = NULL;
            table->count--;
            return;
        }
        else if (head != NULL)
        {
            if (strcmp(item->key, key) == 0)
            {

                LinkedList *node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = CreateItem(node->item->key, node->item->value);
                table->overflow_buckets[index] = head;
                return;
            }

            LinkedList *curr = head;
            LinkedList *prev = NULL;

            while (curr)
            {
                if (strcmp(curr->item->key, key) == 0)
                {
                    if (prev == NULL)
                    {
                        table->overflow_buckets[index] = NULL;
                        return;
                    }
                    else
                    {
                        prev->next = curr->next;
                        curr->next = NULL;
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }
        }
    }
}
void input_from_file(HashTable *ht, int size)
{
    ifstream fp;
    fp.open("GameOfThrones.txt");
    if (!fp.is_open())
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    int i = 0;
    while (i != size)
    {
        i++;
        string key;
        string value;
        getline(fp, key, '=');
        getline(fp, value, '\n');
        char *Value = value.data();
        char *Key = key.data();
        Insert(ht, Key, Value);
    }
}