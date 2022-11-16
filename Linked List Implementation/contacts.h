#ifndef contacts_h
#define contacts_h

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define CALLS 10

typedef enum {FAILURE, SUCCESS} status_code;
typedef enum {PERSONAL, PROFESSIONAL} contact_type;

typedef struct
{
    char day[15];
    char duration[15];
} date;

typedef struct contact_tag
{
    int s_no;
    char f_name[20];
    char l_name[20];
    char mo_number[15];
    char email[40];
    int office_no;      //
    char office[20];    //      Extras for professional contacts
    char address[20];   //
    char type[20];
    int time;
    int no_of_calls;
    date call_date[CALLS];
    contact_type c_type;
    struct contact_tag *next;
} contact;

void display_contact (contact* q);
contact* scan_pers_pb (void);
contact* scan_prof_pb (void);
void indexing (contact** lpptr);
void display (contact* lptr, contact_type ct);
contact* insert_contact (contact* lptr);
void edit_contact(int i, contact *lptr);
contact* delete_contact (int i, contact* lptr);
void search_contact(contact* lptr);
contact* divide (contact* lptr);
contact* union_contacts (contact* lptr, contact* nptr);
contact* Mergesort (contact* list_ptr);
contact* reverse (contact* lptr);
void remove_duplicates (contact *lptr);
void set_time (contact* lptr);
contact* merge_time (contact* lptr, contact* nptr);
contact* mergesort_time (contact* list_ptr);
contact* merge_type (contact* lptr, contact* nptr);
contact* mergesort_type (contact* list_ptr);
void DeleteAtStart (contact** lpptr);
void DeleteList (contact** lpptr);

#endif /* contacts_h */
