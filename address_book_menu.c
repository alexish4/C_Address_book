#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//#include "abk_fileops.h"
//#include "abk_log.h"
//#include "abk_menus.h"
//#include "abk.h"
#include "address_book_menu.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 
	int number = 0;

	if(*msg != '\0')
		printf("%s", msg);

	if(type == NUM) {
		number = checkIntChar();

		switch(number) {
			case 0: return e_exit;
			case 1: return e_add_contact;
			case 2: return e_search_contact;
			case 3: return e_edit_contact;
			case 4: return e_delete_contact;
			case 5: return e_list_contacts;
			case 6: return e_save;
			default: return e_exit;
		}
	}
	else if (type == CHAR) {
		bool check = checkChar();
		if(check == false)
			return 'N';
		else 
			return 'Y';
	}
	else {
		return e_back;
	}
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		//main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	// system("clear");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");


		if(option == e_exit) 
			break;
		else if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			//continue;
		}

		switch (option)
		{
			case e_add_contact:
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				displayList(address_book);
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	int selection;
	int indexOfEmail = 0, indexOfPhone = 0;
	bool check = true;

	while (check)
	{
		printf("\n");
		printf("Please choose an option:\n");
		printf("0. Add contact name\n");
		printf("1. Add phone number to contact\n");
		printf("2. Add e-mail address to contact\n");
		printf("3. Go back to the main menu\n");

		selection = checkIntChar();

		if (selection == 0)
		{
			printf("What is the contact name:\n");
			scanf("%s", address_book -> list[address_book->count].name[0]);
		}
		else if (selection == 1)
		{
			if (indexOfPhone < 5)
			{
				printf("What is the phone number:\n");
				scanf("%s", address_book -> list[address_book->count].phone_numbers[indexOfPhone]);
				indexOfPhone++;
			}
			else 
				printf("You can not enter more than 5 phone numbers");
		}
		else if (selection == 2)
		{
			if (indexOfEmail < 5)
			{
				printf("What is the e-mail:\n");
				scanf("%s", address_book -> list[address_book->count].phone_numbers[indexOfEmail]);
				indexOfEmail++;
			}
			else 
				printf("You can not enter more than 5 e-mails");
		}
		else if (selection == 3)
		{
			return e_back;
		}	
	}
	address_book->list[address_book->count].si_no = address_book->count + 1;
	address_book->count++;

}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}

void displayList(AddressBook *address_book) {
	printf("=================================================================================================================\n");
	printf("%c %-10s %c %-30s %c %-30s %c %-30s %c\n",':',"S.No",':', "Name", ':', "Phone No", ':', "Email ID",':');
	printf("=================================================================================================================\n");
	for(int j = 0; j < address_book->count;j++) {
		printf("%c %-10d %c %-30s %c %-30s %c %-30s %c\n",':',address_book->list[j].si_no,':', address_book->list[j].name[0], ':', address_book->list[j].phone_numbers[0], ':', address_book->list[j].email_addresses[0], ':');
		for(int i = 1; i < PHONE_NUMBER_COUNT; i++) {
			printf("%c %-10s %c %-30s %c %-30s %c %-30s %c\n",':',"",':', "", ':', ((strcmp(address_book->list[j].phone_numbers[i],"[empty]") == 0) ? "" : address_book->list[j].phone_numbers[i]), ':', ((strcmp(address_book->list[j].email_addresses[i],"[empty]") == 0) ? "" : address_book->list[j].email_addresses[i]),':');
		}
		printf("=================================================================================================================\n");
	}
}

int checkIntChar() {
    int number = 0, buffer = 0;
	

    while(true) {
        if((scanf("%d", &number)) != 1) {
            printf("Invalid input!\n");
            while((number = getchar()) != EOF && number != '\n');
        }
        else if(number < 0) {
            printf("Invalid input!\n");
            //clear buffer
            while((number = getchar()) != EOF && number != '\n');
        }
        else {
            break;
        }
    }
    //clear buffer
    while((buffer = getchar()) != EOF && buffer != '\n');
    return number;
}

bool checkChar() {
    int number = 0;

    //Clear the buffer if the inputs are wrong
    while(true) {
        number = getchar();
        if(number == 'y' || number == 'Y') {
            return true;
        }
        else if(number == 'n' || number == 'N') {
            return false;
        }
    }
}
