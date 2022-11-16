#include "contacts.h"

void display_contact (contact* q)
{
    if (q->c_type == PERSONAL)
    {
        printf("%d\t%s\t%s\t%s\t%s\t%s\t%d\n", q->s_no, q->f_name, q->l_name, q->mo_number, q->email, q->type, q->no_of_calls);
    }
    else
    {
        printf("%d\t%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s\t%d\n", q->s_no, q->f_name, q->l_name, q->mo_number, q->email, q->office_no, q->office, q->address, q->type, q->no_of_calls);
    }
    for (int i = 0; i < q->no_of_calls; i++)
    {
        printf("%s\t%s\n", q->call_date[i].day, q->call_date[i].duration);
    }
}

contact* scan_pers_pb (void)               //scans input from file
{
    FILE *fp;
    fp = fopen("pers_pb.txt", "r");

    if(fp == 0)
    {
        perror("fopen");
        exit(1);
    }
    
    char str[100];
    int flag1 = 0;
    contact *lptr = NULL;
    
    while (flag1 == 0)
    {
        fgets(str, 100, fp);
        if (lptr != NULL)
        {
            if (feof(fp) != 0)
            {
                flag1++;
            }
        }
        if (flag1 == 0)
        {
            contact *q;
            q = (contact *)malloc(sizeof(contact));
            sscanf(str, "%d %s %s %s %s %s %d", &q->s_no, q->f_name, q->l_name, q->mo_number, q->email, q->type, &q->no_of_calls);
            q->c_type = PERSONAL;
            if (q->no_of_calls > 0)
            {
                for (int i = 0; i < q->no_of_calls; i++)
                {
                    fgets(str, 100, fp);
                    char dates[15], time[15];
                    sscanf(str, "%s %s", dates, time);
                    strcpy(q->call_date[i].day, dates);
                    strcpy(q->call_date[i].duration, time);
                }
            }
            q->next = lptr;
            lptr = q;
        }
    }
    fclose(fp);
    return lptr;
}

contact* scan_prof_pb (void)               //scans input from file
{
    FILE *fp;
    fp = fopen("prof_pb.txt", "r");
    if(fp == 0)
    {
        perror("fopen");
        exit(1);
    }

    char str[100];
    int flag1 = 0;
    contact *lptr = NULL;
    
    while (flag1 == 0)
    {
        fgets(str, 100, fp);
        if (lptr != NULL)
        {
            if (feof(fp) != 0)
            {
                flag1++;
            }
        }
        if (flag1 == 0)
        {
            contact *q;
            q = (contact *)malloc(sizeof(contact));
            sscanf(str, "%d %s %s %s %s %d %s %s %s %d", &q->s_no, q->f_name, q->l_name, q->mo_number, q->email, &q->office_no, q->office, q->address, q->type, &q->no_of_calls);
            q->c_type = PROFESSIONAL;
            if (q->no_of_calls > 0)
            {
                for (int i = 0; i < q->no_of_calls; i++)
                {
                    fgets(str, 100, fp);
                    char dates[15], time[15];
                    sscanf(str, "%s %s", dates, time);
                    strcpy(q->call_date[i].day, dates);
                    strcpy(q->call_date[i].duration, time);
                }
            }
            q->next = lptr;
            lptr = q;
        }
    }
    fclose(fp);
    return lptr;
}

void indexing (contact** lpptr)     //indexes all contacts in the phonebook
{
    int i = 1;
    contact *nptr;
    nptr = *lpptr;
    while (nptr != NULL)
    {
        nptr->s_no = i;
        i++;
        nptr = nptr->next;
    }
}

void display (contact* lptr, contact_type ct)
{
    indexing(&lptr);
    contact* nptr;
    nptr = lptr;
            
    if (ct == PERSONAL)
    {
        printf("No\tName\t\tMobile\tEmail\tType\tNo of calls\n");
        while (nptr != NULL)
        {
            if (nptr->c_type == ct)
            {
                display_contact(nptr);
            }
            nptr = nptr->next;
        }
    }
    else if (ct == PROFESSIONAL)
    {
        printf("\nNo\tName\t\tMobile\tEmail\tOfficeNo\tOffice\tAddress\tType\tNo of calls\n");
        while (nptr != NULL)
        {
            if (nptr->c_type == ct)
            {
                display_contact(nptr);
            }
            nptr = nptr->next;
        }
    }
    else
    {
        while (nptr != NULL)
        {
            display_contact(nptr);
            nptr = nptr->next;
        }
    }
}

contact* insert_contact (contact* lptr)
{
    contact* q;
    q = (contact *)malloc(sizeof(contact));
    int t;
    q->s_no = 0;
    printf("Enter the following fields:\nFirst Name: ");
    scanf("%s", q->f_name);
    printf("Last name: ");
    scanf("%s", q->l_name);
    printf("Mobile Number: ");
    scanf("%s", q->mo_number);
    printf("Email: ");
    scanf("%s", q->email);
    printf("Contact type(Enter 0 for Personal, 1 for Professional): ");
    scanf("%d", &t);
    if (t == 0)
    {
        q->c_type = PERSONAL;
    }
    else
    {
        q->c_type = PROFESSIONAL;
        printf("Office Number: ");
        scanf("%d", &q->office_no);
        printf("Office: ");
        scanf("%s", q->office);
        printf("Address: ");
        scanf("%s", q->address);
    }
    printf("Type(description): ");
    scanf("%s", q->type);
    printf("Number of calls made to this contact: ");
    scanf("%d", &q->no_of_calls);
    for (t = 0; t < q->no_of_calls; t++)
    {
        printf("Date(dd/mm/yyyy): ");
        scanf("%s", q->call_date[t].day);
        printf("Duration(hh:mm:ss): ");
        scanf("%s", q->call_date[t].duration);
    }
    
    q->next = lptr;
    lptr = q;
    
    printf("New contact added\n");
    display_contact(q);
    return lptr;
}

void edit_contact(int i, contact *lptr)
{
    contact* q;
    q = lptr;
    while (q->s_no != i && q != NULL)
    {
        q = q->next;
    }
    if (q == NULL)
    {
        printf("Contact with index %d not found\n", i);
    }
    else
    {
        printf("Enter corresponding number of field to be edited:\n1.First name\n2.Last name\n3. Mobile Number\n4.Email\n5.Type\n6.Number of calls/Date/Duration\n7.Contact type\n");
        if (q->c_type == PROFESSIONAL)
        {
            printf("8.Office Number\n9.Office/Institute\n10.Address\n");
        }
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
        {
            printf("Enter new first name: ");
            scanf("%s", q->f_name);
        }
        if (opt == 2)
        {
            printf("Enter new last name: ");
            scanf("%s", q->l_name);
        }
        if (opt == 3)
        {
            printf("Enter new mobile number: ");
            scanf("%s", q->mo_number);
        }
        if (opt == 4)
        {
            printf("Enter new email: ");
            scanf("%s", q->email);
        }
        if (opt == 5)
        {
            printf("Enter new type: ");
            scanf("%s", q->type);
        }
        if (opt == 6)
        {
            printf("Enter number of calls: ");
            scanf("%d", &q->no_of_calls);
            for (int i = 0; i < q->no_of_calls; i++)
            {
                printf("Enter date(dd/mm/yy): ");
                {
                    scanf("%s", q->call_date[i].day);
                }
                printf("Enter duration(hh:mm:ss): ");
                {
                    scanf("%s", q->call_date[i].duration);
                }
            }
        }
        if (opt == 7)
        {
            printf("Enter contact type (0 for personal, 1 for professional): ");
            scanf("%d", &q->c_type);
        }
        if (q->c_type == 1)
        {
            if (opt == 8)
            {
                printf("Enter new office number: ");
                scanf("%d", &q->office_no);
            }
            if (opt == 9)
            {
                printf("Enter new office/institute name: ");
                scanf("%s", q->office);
            }
            if (opt == 10)
            {
                printf("Enter new address: ");
                scanf("%s", q->address);
            }
        }
        printf("Contact is modified\n");
        display_contact(q);
    }
}

contact* delete_contact (int i, contact* lptr)
{
    contact* q;
    q = lptr;
    while (q->s_no != i && q != NULL)
    {
        q = q->next;
    }
    if (q == NULL)
    {
        printf("Contact not found\n");
    }
    else
    {
        if (q == lptr)
        {
            lptr = lptr->next;
            printf("Contact of %s %s has been deleted\n", q->f_name, q->l_name);
            free(q);
        }
        else
        {
            contact* p;
            p = lptr;
            while ((p->next)->s_no != i)
            {
                p = p->next;
            }
            p->next = (p->next)->next;
            printf("Contact of %s %s has been deleted\n", q->f_name, q->l_name);
            free(q);
        }
    }
    return lptr;
}

void search_contact(contact* lptr)
{
    int choice, count = 0;
    char str[20];
    contact* q;
    q = lptr;
    printf("Search contact through name(0), number(1), address(2): ");
    scanf("%d", &choice);
    if (choice == 0)
    {
        printf("Enter name: ");
        scanf("%s", str);
        while (q != NULL)
        {
            if (strstr(q->f_name, str) != NULL || strstr(q->l_name, str) != NULL)
            {
                count++;
                display_contact(q);
            }
            q = q->next;
        }
        printf("%d contact(s) found.", count);
    }
    if (choice == 1)
    {
        printf("Enter mobile number: ");
        scanf("%s", str);
        while (q != NULL)
        {
            if (strstr(q->mo_number, str) != NULL)
            {
                count++;
                display_contact(q);
            }
            q = q->next;
        }
        printf("%d contact(s) found.", count);
    }
    if (choice == 2)
    {
        printf("Enter address: ");
        scanf("%s", str);
        while (q != NULL)
        {
            if (q->c_type == PROFESSIONAL && strstr(q->address, str) != NULL)
            {
                count++;
                display_contact(q);
            }
            q = q->next;
        }
        printf("%d contact(s) found.", count);
    }
}

contact* divide (contact* lptr)
{
    contact *nptr, *fast, *slow;
    slow = lptr;
    fast = lptr->next->next;
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
        if (fast != NULL)
        {
            fast = fast->next;
        }
    }
    nptr = slow->next;
    slow->next = NULL;
    return nptr;
}

contact* union_contacts (contact* lptr, contact* nptr)  //merges two phonebooks
{
    contact *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (strcmp(ptr1->f_name, ptr2->f_name) < 0)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else if (strcmp(ptr1->f_name, ptr2->f_name) == 0 && strcmp(ptr1->l_name, ptr2->l_name) < 0)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else if (strcmp(ptr1->f_name, ptr2->f_name) == 0 && strcmp(ptr1->l_name, ptr2->l_name) == 0 && strcmp(ptr1->mo_number, ptr2->mo_number) < 0)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    
    tail = result;
    while ((ptr1 != NULL) && (ptr2 != NULL))
    {
        if (strcmp(ptr1->f_name, ptr2->f_name) < 0)
        {
            tail = tail->next = ptr1;
            ptr1 = ptr1->next;
        }
        else if (strcmp(ptr1->f_name, ptr2->f_name) == 0 && strcmp(ptr1->l_name, ptr2->l_name) < 0)
        {
            tail = tail->next = ptr1;
            ptr1 = ptr1->next;
        }
        else if (strcmp(ptr1->f_name, ptr2->f_name) == 0 && strcmp(ptr1->l_name, ptr2->l_name) == 0 && strcmp(ptr1->mo_number, ptr2->mo_number) < 0)
        {
            tail = tail->next = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail = tail->next = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 != NULL)
    {
        tail->next = ptr1;
    }
    else
    {
        tail->next = ptr2;
    }
    return result;
}

contact* Mergesort (contact* list_ptr)
{
    contact *nptr, *lptr;
    lptr = list_ptr;
    if ((lptr != NULL) && (lptr->next != NULL))
    {
        nptr = divide(lptr);
        lptr = Mergesort(lptr);
        nptr = Mergesort(nptr);
        lptr = union_contacts(lptr, nptr);
    }
    return lptr;
}

contact* reverse (contact* lptr)
{
    contact *head, *middle, *tail;
    head = lptr;
    middle = NULL;
    while (head != NULL)
    {
        tail = middle;
        middle = head;
        head = head->next;
        middle->next = tail;
    }
    return middle;
}

void remove_duplicates (contact *lptr)
{
    contact *q, *p;
    q = lptr;
    while (q->next != NULL)
    {
        if (strcmp(q->f_name, (q->next)->f_name) == 0 && strcmp(q->mo_number, q->next->mo_number) == 0)
        {
            p = q->next;
            q->next = p->next;
            free(p);
        }
        else
        {
            q = q->next;
        }
    }
    printf("All duplicates removed\n");
}

void set_time (contact* lptr)
{
    contact* q;
    q = lptr;
    while (q != NULL)
    {
        int t = 0;
        for (int i = 0; i < q->no_of_calls; i++)
        {
            t += 3600*(10*(q->call_date[i].duration[0] - '0') + (q->call_date[i].duration[1] - '0')) + 60*(10*(q->call_date[i].duration[3] - '0') + (q->call_date[i].duration[4] - '0')) + 10*(q->call_date[i].duration[6] - '0') + (q->call_date[i].duration[7] - '0');
        }
        q->time = t;
        q = q->next;
    }
}

contact* merge_time (contact* lptr, contact* nptr)
{
    contact *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (ptr1->time > ptr2->time)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    tail = result;
    while ((ptr1 != NULL) && (ptr2 != NULL))
    {
        if (ptr1->time > ptr2->time)
        {
            tail = tail->next = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail = tail->next = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 != NULL)
    {
        tail->next = ptr1;
    }
    else
    {
        tail->next = ptr2;
    }
    return result;
}

contact* mergesort_time (contact* list_ptr)
{
    contact *nptr, *lptr;
    lptr = list_ptr;
    if ((lptr != NULL) && (lptr->next != NULL))
    {
        nptr = divide(lptr);
        lptr = mergesort_time(lptr);
        nptr = mergesort_time(nptr);
        lptr = merge_time(lptr, nptr);
    }
    return lptr;
}

contact* merge_type (contact* lptr, contact* nptr)
{
    contact *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (ptr1->c_type > ptr2->c_type)
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    tail = result;
    while ((ptr1 != NULL) && (ptr2 != NULL))
    {
        if (ptr1->c_type > ptr2->c_type)
        {
            tail = tail->next = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail = tail->next = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 != NULL)
    {
        tail->next = ptr1;
    }
    else
    {
        tail->next = ptr2;
    }
    return result;
}

contact* mergesort_type (contact* list_ptr)
{
    contact *nptr, *lptr;
    lptr = list_ptr;
    if ((lptr != NULL) && (lptr->next != NULL))
    {
        nptr = divide(lptr);
        lptr = mergesort_type(lptr);
        nptr = mergesort_type(nptr);
        lptr = merge_type(lptr, nptr);
    }
    return lptr;
}

void DeleteAtStart (contact** lpptr)
{
    contact* lptr = *lpptr;
    contact* nptr = lptr;
    if (lptr != NULL)
    {
        lptr = lptr->next;
        free(nptr);
        *lpptr = lptr;
    }
}

void DeleteList (contact** lpptr)
{
    contact* lptr;
    contact* nptr;
    lptr = *lpptr;
    nptr = lptr;
    while (lptr != NULL)
    {
       DeleteAtStart(&lptr);
    }
    *lpptr = NULL;
}
