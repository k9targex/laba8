
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <cctype>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <locale.h>

#include "CheckInt.h"
#include "FuncToTable.h"
#include "HashTable.h"
#include "Menu.h"
using namespace std;
main()
{
    printf("Avalibale 60 lines, how much u want to upload?\n");
    int lines = Inputcheck();
    while (lines < 1 || lines > 60)
    {
        printf(RED "Error\n" RESET);
        lines = Inputcheck();
    }
    printf("Input size of hashtable\n");
    int size = Inputcheck();
    while (size < 1 || size > 100)
    {
        printf(RED "Error\n" RESET);
        size = Inputcheck();
    }
    HashTable *ht = CreateTable(size);
    input_from_file(ht, lines);
    Menu(ht);
    return 0;
}