#pragma once
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <cctype>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "CheckInt.h"

#include <locale.h>

#include "HashTable.h"

using namespace std;
// Ht_item *CreateItem(char *key, char *value);

char *Search(HashTable *table, char *key);

void Insert(HashTable *table, char *key, char *value);

void PrintTable(HashTable *table);

void PrintSearch(HashTable *table, char *key, int size);

void Delete(HashTable *table, char *key);

void input_from_file(HashTable *ht, int size);
