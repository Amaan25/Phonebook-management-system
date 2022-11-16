#include "phonebooks.h"

void pb_display (contact* lptr1, contact* lptr2)
{
    phonebook* pb1, *pb2, *ptr;
    pb1 = (phonebook *)malloc(sizeof(phonebook));
    pb2 = (phonebook *)malloc(sizeof(phonebook));
    pb1->next = pb2;
    pb2->next = NULL;
    pb1->pb = lptr1;
    pb2->pb = lptr2;
    strcpy(pb1->f_name, "Ravi");
    strcpy(pb1->l_name, "Sharma");
    strcpy(pb1->mo_number, "4537976421");
    strcpy(pb1->address, "Churchgate");
    strcpy(pb2->f_name, "Akash");
    strcpy(pb2->l_name, "Verma");
    strcpy(pb2->mo_number, "6754097654");
    strcpy(pb2->address, "Bandra");

    ptr = pb1;
    while (ptr != NULL)
    {
        set_time(ptr->pb);
        
        ptr->pb = mergesort_time(ptr->pb);
        printf("Phonebook owner:\n%s\t%s\t%s\t%s\n", ptr->f_name, ptr->l_name, ptr->mo_number, ptr->address);
        printf("Phonebook:\n");
        display(ptr->pb, 2);
        printf("\n");
        ptr = ptr->next;
    }
    
    free(pb1);
    free(pb2);
}
