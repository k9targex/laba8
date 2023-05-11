
#include "Menu.h"
// #include "FuncToTable.h"

int Menu(HashTable *ht)
{
    char leave;
    do
    {
        rewind(stdin);
        printf("Menu\n0)Print table\n1)Add your line\n2)Delete line\n3)Find line\n4)Exit\n");
        switch (Inputcheck())
        {
        case 0:
        {
            PrintTable(ht);
            break;
        }
        case 1:
        {
            printf("Enter line\n");
            string line;
            getline(cin, line);
            printf("Enter value\n");
            string value;
            getline(cin, value);
            Insert(ht, line.data(), value.data());
            Space();
            break;
        }
        case 2:
        {
            printf("Enter line to delete\n");
            string line;
            getline(cin, line);
            // CreateString(line);
            Delete(ht, line.data());
            Space();
            break;
        }
        case 3:
        {
            printf("Enter line to search\n");
            string line;
            getline(cin, line);
            PrintSearch(ht, line.data(), ht->size);
            Space();

            break;
        }
        case 4:
        {
            return 0;
        }
        default:
        {
            printf("\n\x1B[1;31mInvalid input.Try again.\n\033[0m ");
            return Menu(ht);
        }
        }
        printf("\n\x1B[1;34mPress \x1B[1;35m  SPACE \x1B[1;34mto continue. Or another symbol to leave \033[0m \n");
        rewind(stdin);
        leave = _getch();
    } while (leave == ' ');
    return 0;
}