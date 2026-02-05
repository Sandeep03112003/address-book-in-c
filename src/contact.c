#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    if(addressBook->contactCount==0)
    {
       printf("\n=============================================\n");
       printf("        Your Address Book is EMPTY!          \n");
       printf("     Please add contacts to get started.     \n");
       printf("=============================================\n\n");

    }
    else{
    printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-14s | %-49s |\n", "No", "Name", "Phone", "Email");
    printf("+-----+----------------------+----------------+---------------------------------------------------+\n");

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("| %-3d | %-20s | %-14s | %-49s |\n", i + 1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
}
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    int size,i,flag;
    printf("How many contacts do you want to create? : ");
     scanf("%d",&size);
    if(size<=(MAX_CONTACTS-addressBook->contactCount)){
    for( i=0;i<size ;i++){
    char name[30];
    //validation of name
    printf("Enter the name [max 20 characters] :");
        scanf(" %49[^\n]", name);
      validation_name(name);
      strcpy(addressBook->contacts[addressBook->contactCount].name,name);
      //validation of phonenumber
      char phone[20];
              do{
                 printf("Enter the phone number[max 10 characters] :");
                 scanf(" %19[^\n]", phone);
                 validation_phone(phone);
                 flag=0;

                 int ret=is_unique_phone(phone,addressBook);
                 if(ret==1)
                 {
                      flag=1;
                 }
                 if(!flag){
                    printf("You entered existing number .Try again\n");
                 }
                }while(!flag);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);

      //validation of of email
      char mail[50];
      do{
                 printf("Enter the Email[max 50 characters]: ");
                 scanf(" %49[^\n]", mail);
                 validation_mail(mail);
                 flag=0;

                 int ret=is_unique_email(mail,addressBook);
                 if(ret==1)
                 {
                      flag=1;
                 }
                 if(!flag){
                    printf("You entered existing Email .Try again\n");
                 }
                }while(!flag);
      strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
     addressBook->contactCount++;
     printf("                                       \n"
            "[======Contact Saved Sucessfully======]\n"
            "                                        \n");
     }
    }
     else
     {
     printf("Note: You can store a maximum of 100 contacts.Already %d contacts are exists\n",addressBook->contactCount);

    }

}
    void searchContact(AddressBook *addressBook) 
{
    char name[50], phone[20], mail[50];

    int choice;
    do{
    printf("\n==============================\n");
printf("       Search Contacts\n");
printf("==============================\n");
printf("1. Search by Name\n");
printf("2. Search by Phone Number\n");
printf("3. Search by Email\n");
printf("------------------------------\n");
printf("Select your choice: ");

    scanf(" %d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the name [max 20 characters] : ");
            scanf(" %49[^\n]", name);
            validation_name(name);
            if(search_by_name(name, addressBook))
            {
                 printf("\n------------------ Contact Not Found ------------------\n");

            }
            break;
        case 2:
            printf("Enter the phone number[max 10 characters] : ");
            scanf(" %19[^\n]", phone);
            validation_phone(phone);
             if(search_by_phone_number(phone, addressBook))
            {
                 printf("\n------------------ Contact Not Found ------------------\n");

            }
            break;
        case 3:
            printf("Enter the Email[max 50 characters]: ");
            scanf(" %49[^\n]", mail);
            validation_mail(mail);
             if(search_by_mail(mail, addressBook)==1)
            {
                 printf("\n------------------ Contact Not Found ------------------\n");

            }
            break;
        default:
            printf("Enter a valid choice please select the correct one :\n");
    }
} while (choice < 1 || choice > 3 ); 

}

void editContact(AddressBook *addressBook)
{
    char name[50], phone[20],mail[50],search_value[50];
     int choice,flag=0;
do {
    printf("\n==============================\n");
printf("    Search Contact To Edit\n");
printf("==============================\n");
 printf("1.Name:\n");
    printf("2.Phone number:\n");
    printf("3.Email:\n");
printf("Select your choice: ");

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the name [max 20 characters] : ");
            scanf(" %49[^\n]", name);
            validation_name(name);
            if(search_by_name(name, addressBook))
            {
                 flag=1;

            }
            else{
            strcpy(search_value,name);
            }
            break;
        case 2:
            printf("Enter the phone number[max 10 characters] : ");
            scanf(" %19[^\n]", phone);
            validation_phone(phone);
            if(search_by_phone_number(phone, addressBook))
            {
                flag=1;

            }
            else{
            strcpy(search_value,phone);
            }
            break;
        case 3:
            printf("Enter the Email[max 50 characters]: ");
            scanf(" %49[^\n]", mail);
            validation_mail(mail);
            if(search_by_mail(mail, addressBook))
            {
                flag=1;

            }
            else{
            strcpy(search_value,mail);
            }
            break;
        default:
            printf("Enter a valid choice please select the correct one :\n");
    }
} while (choice < 1 || choice > 3); 
if(flag)
{
     printf("\n------------------ Contact Not Found ------------------\n");

}
else
{
     edit_by_contact(search_value,addressBook);
}


}

void deleteContact(AddressBook *addressBook)
{
    int option,i;
    char search_value[50];
    do{
        printf("\n===== Delete Contact By =====\n");
        printf("1.Name:\n");
        printf("2.Phone number:\n");
        printf("3.Email:\n");
    char name[50],phone[20],email[50];
    printf("Enter the choice : ");
    scanf("%d",&option);
    switch(option)
    {
        case 1: printf("Enter the name [max 20 characters] :  ");
                 scanf(" %49[^\n]",name);
                 validation_name(name);
                 if(search_by_name(name,addressBook))
                 {
                    printf("\n------------------ Contact Not Found ------------------\n");

                 }
                 else{
                 strcpy(search_value,name);
                 delete_by_name(search_value,addressBook);
                 printf("\n*** Contact Deleted Successfully ***\n");
                 }
                 break; 
        case 2: printf("Enter the phone number[max 10 characters] : ");
                 scanf(" %19[^\n]",phone);
                 validation_phone(phone);
                 if(search_by_phone_number(phone,addressBook))
                 {
                    printf("\n------------------ Contact Not Found ------------------\n");

                 }
                 else{ strcpy(search_value,phone);
                 delete_by_phone_number(search_value,addressBook);
                 printf("\n*** Contact Deleted Successfully ***\n");
                 }
                 break; 
        case 3: printf("Enter the Email[max 50 characters]: ");
                 scanf(" %49[^\n]",email);
                 validation_mail(email);
                 if(search_by_mail(email,addressBook))
                 {
                    printf("\n------------------ Contact Not Found ------------------\n");

                 }
                 else{
                 strcpy(search_value,email);
                 delete_by_mail(search_value,addressBook);
                 printf("\n*** Contact Deleted Successfully ***\n");
                 }
                  break;
        default: printf("Enter valid option.\n");          
    }
 } while(option<1 || option>3);
}

void validation_name(char *name){
int valid;

    do {
        valid = 1; // assume valid
        for (int i = 0; name[i] != '\0'; i++) {
            if (!(isalpha(name[i]) || name[i] == ' ')) { 
                valid = 0; // invalid
                break;
            }
        }
        
        if (!valid) {
            printf("Invalid name. Please try again.\n");
            printf("Enter the name [max 20 characters] :");
            scanf("%49s[^\n]",name);
        }

    } while (!valid);
}
int is_unique_name(char *name,AddressBook *addressBook)
{
    int count=0;
    for (int j = 0; j < addressBook->contactCount; j++)
            {
               if (strcmp(addressBook->contacts[j].name, name) == 0)
                {
                    count++;
                 }
             }
       if(count>1)
       {
        return 0;
       }
       else{
        return 1;
       }
}
void validation_phone(char *phone ) {
    int ret;
    do {
         ret = 1; // assume valid
          if (strlen(phone) != 10) {
            ret = 0;
          }
        
        else{
              for (int i = 0; phone[i] != '\0'; i++) {
                if (!(phone[i] >= '0' && phone[i] <= '9')) {
                    ret = 0; // invalid
                    break;
                }
            }
        }
        if (!ret) {
           printf("Invalid phone number (10 digits required or invalid characters).\n");
           printf("Enter the phone number [max 10 characters]: ");
            scanf(" %19[^\n]",phone);
        }
    } while (!ret);
}
int is_unique_phone(char *phone,AddressBook *addressBook)
{
     for (int j = 0; j < addressBook->contactCount; j++)
            {
               if (strcmp(addressBook->contacts[j].phone, phone) == 0)
                {
                     return 0; // not unique
                     break;
                 }
             }
             return 1;
}
void validation_mail(char *mail) {
    int flag;

    do {
        flag = 1; // assume valid
        // 1. Must contain exactly one '@'
        char *at = strchr(mail, '@');
        if (!at || at != strrchr(mail, '@') || at == mail || *(at + 1) == '\0') {
            flag = 0;
        }

        // 2. Must contain at least one '.' after '@' and not immediately after it
        char *dot = strrchr(mail, '.');
        if (!dot || dot < at + 2 || *(dot + 1) == '\0') {
            flag = 0;
        }
        if (dot && strlen(dot + 1) < 2) {
            flag = 0;
        }
        for (int i = 0; mail[i] != '\0'; i++) {
            if (mail[i] == ' ') {
                flag = 0;
                break;
            }
        }

        // 5. No consecutive dots
        if (strstr(mail, "..") != NULL) {
            flag = 0;
        }
        if (!flag) {
            printf("Invalid email. Please try again.\n");     // ======= IF INVALID, ASK AGAIN =======
            printf("Enter the Email[max 50 characters]: ");
            scanf(" %49[^\n]", mail);
        }

    } while (!flag);
}
int is_unique_email(char *mail,AddressBook *addressBook)
{
    for (int j = 0; j < addressBook->contactCount; j++)
            {
               if (strcmp(addressBook->contacts[j].email, mail) == 0)
                {
                     return 0; // not unique
                     break;
                 }
             }
             return 1;

}

int search_by_name(char *name, AddressBook *addressBook)
{
    int found = 0;
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (strcmp(addressBook->contacts[j].name, name) == 0)
        {
            if (!found) 
            {
                printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
                printf("| %-3s | %-20s | %-14s | %-49s |\n", "No", "Name", "Phone", "Email");
                printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
            }

            printf("| %-3d | %-20s | %-14s | %-49s |\n",
                   j + 1,
                   addressBook->contacts[j].name,
                   addressBook->contacts[j].phone,
                   addressBook->contacts[j].email);
            printf("+-----+----------------------+----------------+---------------------------------------------------+\n");

            found = 1; 
        }
    }

    if (found)
        return 0; 
    else
        return 1;
}

int search_by_phone_number(char *phone, AddressBook *addressBook)
{

      int flag=0; 
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if ((strcmp(addressBook->contacts[j].phone, phone) != 0))
        {
           flag=1;
        }
    else
    {
        printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-14s | %-49s |\n", "No", "Name", "Phone", "Email");
    printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
        printf("| %-3d | %-20s | %-14s | %-49s |\n", 
            j + 1, 
            addressBook->contacts[j].name,
            addressBook->contacts[j].phone,
            addressBook->contacts[j].email);
    

    printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
    return 0;
    }
}
if(flag)
{
    return 1;
}
}
int search_by_mail(char *mail, AddressBook *addressBook)
{
    int flag;
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if ((strcmp(addressBook->contacts[j].email, mail) != 0))
        {
           flag=1;
        }
        else{
        printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-14s | %-49s |\n", "No", "Name", "Phone", "Email");
    printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
        printf("| %-3d | %-20s | %-14s | %-49s |\n", 
            j + 1, 
            addressBook->contacts[j].name,
            addressBook->contacts[j].phone,
            addressBook->contacts[j].email);
    

    printf("+-----+----------------------+----------------+---------------------------------------------------+\n");
     flag =0;
     return 0;
}
    }
    if(flag)
    {
        return 1;
    }
}
void edit_by_contact(char *search_value, AddressBook *addressBook)
{
    int matches[100];   // store matching indexes
    int matchCount = 0;

    // Find all matching contacts
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if ((strcmp(addressBook->contacts[j].name, search_value) == 0) ||
            (strcmp(addressBook->contacts[j].phone, search_value) == 0) ||
            (strcmp(addressBook->contacts[j].email, search_value) == 0))
        {
            matches[matchCount++] = j;
        }
    }

    if (matchCount == 0)
    {
        printf("No contact found with the given search value.\n");
        return;
    }

    int index;
    if (matchCount == 1)
    {
        index = matches[0]; // only one match
    }
    else
    {
        // Show all matches
        printf("Multiple contacts found:\n");
        for (int i = 0; i < matchCount; i++)
        {
            int j = matches[i];
            printf("%d. %s | %s | %s\n",
                   i + 1,
                   addressBook->contacts[j].name,
                   addressBook->contacts[j].phone,
                   addressBook->contacts[j].email);
        }
        printf("Enter the index to edit: ");
        int choice;
        scanf("%d", &choice);
        if (choice < 1 || choice > matchCount)
        {
            printf("Invalid choice.\n");
            return;
        }
        index = matches[choice - 1];
    }
    int option, flag;
    char new_name[50], new_phone[20], new_email[50];

    do
    {
        printf("\n1. Edit Name\n");
        printf("2. Edit Phone\n");
        printf("3. Edit Email\n");
        printf("Select the choice: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Enter the new name: ");
            scanf(" %49[^\n]", new_name);
            validation_name(new_name);
            strcpy(addressBook->contacts[index].name, new_name);
            break;

        case 2:
            do {
                flag = 0;
                printf("Enter the new number: ");
                scanf(" %19s", new_phone);
                validation_phone(new_phone);
                if (is_unique_phone(new_phone, addressBook)) {
                    strcpy(addressBook->contacts[index].phone, new_phone);
                    flag = 1;
                } else {
                    printf("Number already exists. Try again.\n");
                }
            } while (!flag);
            break;

        case 3:
            do {
                flag = 0;
                printf("Enter the new Email: ");
                scanf(" %49[^\n]", new_email);
                validation_mail(new_email);
                if (is_unique_email(new_email, addressBook)) {
                    strcpy(addressBook->contacts[index].email, new_email);
                    flag = 1;
                } else {
                    printf("Email already exists. Try again.\n");
                }
            } while (!flag);
            break;

        default:
            printf("Enter valid option.\n");
        }
    } while (option < 1 || option > 3);

    printf("\n------------------------------------------------\n");
    printf("  The contact details were updated successfully.\n");
    printf("------------------------------------------------\n");
}

void delete_by_phone_number(char *search_value,AddressBook *addressBook)
{
    int index;
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if ((strcmp(addressBook->contacts[j].name,search_value) == 0) ||
            (strcmp(addressBook->contacts[j].phone, search_value) == 0) ||
            (strcmp(addressBook->contacts[j].email, search_value) == 0))
        {
            index=j;
        }
    }
    for(int i=index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
}

void delete_by_mail(char *search_value,AddressBook *addressBook)
{
    int index;
   for (int j = 0; j < addressBook->contactCount; j++)
    {
        if ((strcmp(addressBook->contacts[j].name,search_value) == 0) ||
            (strcmp(addressBook->contacts[j].phone, search_value) == 0) ||
            (strcmp(addressBook->contacts[j].email, search_value) == 0))
        {
            index=j;
        }
    }
    for(int i=index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
}
void delete_by_name(char *search_value,AddressBook *addressBook)
{
    int count=0,index;
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (strcmp(addressBook->contacts[j].name, search_value) == 0)
        {
            index=j;
            count++;
        }
    }
    if(count==1)
    {
    for(int i=index;i<addressBook->contactCount;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    }
    else if(count>1)
    {
        printf("Enter the index value: ");
      scanf("%d",&index);
    index-=1;
    for(int i=index;i<addressBook->contactCount;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }  
     addressBook->contactCount--;
}          
}
