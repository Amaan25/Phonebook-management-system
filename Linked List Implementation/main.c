//Amaan Khan BT20CSE065 R3  DSPD-II Assignment 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "contacts.h"
#include "phonebooks.h"

void choose (int c);

int main()
{
    int c;
    printf("Enter a number for corresponding choice:\n1.Insert/Create contact\n2.Edit contact\n3.Delete a contact\n4.Search contacts\n5.Sort contacts\n6.Display contacts\n7.Union of two phonebooks\n8.Remove duplicate contacts\n9.Display list of phonebooks(display contacts in decreasing order of call durations)\n0.Exit\n");
    scanf("%d", &c);
    choose(c);
    return 0;
}

void choose (int c)
{
    contact* lptr1, *lptr2;
    lptr1 = scan_pers_pb();
    lptr2 = scan_prof_pb();
    int u = 0, t;
    contact* lptr = lptr2;      //change phonebook here
    
    while (c != 0)
    {
        if (c == 1)
        {
            lptr = insert_contact(lptr);
        }
        if (c == 2)
        {
            printf("Enter index of contact to be edited: ");
            scanf("%d", &t);
            edit_contact(t, lptr);
        }
        if (c == 3)
        {
            display(lptr, 0);
            display(lptr, 1);
            printf("Enter index of contact to be deleted: ");
            scanf("%d", &t);
            lptr = delete_contact(t, lptr);
        }
        if (c == 4)
        {
            search_contact(lptr);
        }
        if (c == 5)
        {
            printf("Sort in\n1.Ascending order\n2.Descending order\n3.Personal first\n4.Professional first\n");
            scanf("%d", &t);
            if (t == 1)
            {
                lptr = Mergesort(lptr);
                printf("Contacts are sorted in ascending order\n");
            }
            else if (t == 2)
            {
                lptr = Mergesort(lptr);
                lptr = reverse(lptr);
                printf("Contacts are sorted in descending order\n");
            }
            else if (t == 3)
            {
                lptr = mergesort_type(lptr);
                lptr = reverse(lptr);
                printf("Contacts are sorted personals first\n");
            }
            else if (t == 4)
            {
                lptr = mergesort_type(lptr);
                printf("Contacts are sorted professional first\n");
            }
        }
        if (c == 6)
        {
            printf("1.Display personal list\n2.Display professional list\n3.Complete List\n");
            scanf("%d", &t);
            display(lptr, t-1);
        }
        if (c == 7)
        {
            lptr = union_contacts(lptr, lptr1);
            printf("Two phonebooks have been merged\n");
            u++;
        }
        if (c == 8)
        {
            remove_duplicates(lptr);
        }
        if (c == 9)
        {
            pb_display(lptr1, lptr2);
        }
        printf("\nChose next option: ");
        scanf("%d", &c);
    }

    if (u == 0)
    {
        DeleteList(&lptr1);
        DeleteList(&lptr2);
    }
    else
    {
        DeleteList(&lptr);
    }
}
