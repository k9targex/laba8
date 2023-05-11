
#include "HashTable.h"

LinkedList *ListMalloc()
{

    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    return list;
}

LinkedList *InsertToList(LinkedList *list, Ht_item *item)
{
    if (!list)
    {
        LinkedList *head = ListMalloc();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }

    else if (list->next == NULL)
    {
        LinkedList *node = ListMalloc();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList *temp = list;
    while (temp->next->next)
    {
        temp = temp->next;
    }

    LinkedList *node = ListMalloc();
    node->item = item;
    node->next = NULL;
    temp->next = node;

    return list;
}
Ht_item *CreateItem(char *key, char *value)
{
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = (char *)malloc(strlen(key) + 1);
    item->value = (char *)malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

unsigned HashKey(char *key, int size)
{
    unsigned hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash += key[i];
    }
    hash %= size;
    return hash;
}
LinkedList **CreateBuckets(HashTable *table)
{
    LinkedList **buckets = (LinkedList **)calloc(table->size, sizeof(LinkedList *));
    for (int i = 0; i < table->size; i++)
        buckets[i] = NULL;
    return buckets;
}
HashTable *CreateTable(int size)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;
    table->overflow_buckets = CreateBuckets(table);
    return table;
}

void HandleCollision(HashTable *table, int index, Ht_item *item)
{
    LinkedList *head = table->overflow_buckets[index];

    if (head == NULL)
    {
        head = ListMalloc();
        head->item = item;
        head->next = NULL;
        table->overflow_buckets[index] = head;
        return;
    }
    else
    {
        table->overflow_buckets[index] = InsertToList(head, item);
        return;
    }
}