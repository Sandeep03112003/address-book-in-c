#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void validation_name(char *name);
void validation_phone(char *phone);
void validation_mail(char *mail);
int search_by_name(char *name,AddressBook *addressBook);
int search_by_phone_number(char *phone,AddressBook *addressBook);
int search_by_mail(char *email,AddressBook *addressBook);
void delete_by_name(char *search_value,AddressBook *addressBook);
void delete_by_phone_number(char *search_value,AddressBook *addressBook);
void delete_by_mail(char *search_value,AddressBook *addressBook);
void edit_by_contact(char *search_value,AddressBook *addressBook);
int is_unique_phone(char *phone,AddressBook *addressBook);
int is_unique_email(char *email,AddressBook *addressBook);
int is_unique_name(char *value,AddressBook *addressBook);
#endif
