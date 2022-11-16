#ifndef phonebooks_h
#define phonebooks_h

#include <stdio.h>
#include "contacts.h"
typedef struct pb_tag
{
    char f_name[20];
    char l_name[20];
    char mo_number[15];
    char address[20];
    contact* pb;
    struct pb_tag *next;
} phonebook;

void pb_display (contact* lptr1, contact* lptr2);

#endif /* phonebooks_h */
