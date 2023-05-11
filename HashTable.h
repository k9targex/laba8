#pragma once
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <cctype>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
// #include "CheckInt.h"
#include <locale.h>

using namespace std;

struct Ht_item
{
    char *key;
    char *value;
};

struct LinkedList
{
    Ht_item *item;
    LinkedList *next;
};

struct HashTable
{
    LinkedList **overflow_buckets;
    Ht_item **items;
    int size;
    int count;
};

LinkedList *ListMalloc();

LinkedList *InsertToList(LinkedList *list, Ht_item *item);

Ht_item *CreateItem(char *key, char *value);

unsigned HashKey(char *key, int size);

LinkedList **CreateBuckets(HashTable *table);

HashTable *CreateTable(int size);

void HandleCollision(HashTable *table, int index, Ht_item *item);
