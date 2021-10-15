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

	//free(address_book->list);

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
	//fflush(stdout);

	//system("clear");

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
				printf("The data is saved into %s\n",DEFAULT_FILE);
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
				scanf("%s", address_book -> list[address_book->count].email_addresses[indexOfEmail]);
				indexOfEmail++;
			}
			else 
				printf("You can not enter more than 5 e-mails");
		}
		else if (selection == 3)
		{
			address_book->list[address_book->count].si_no = address_book->count + 1;
			address_book->count++;
			return e_back;
		}	
	}
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	//Declaration
	int option;
	char strInput[NAME_LEN];
	int serialNumber = 0;

	//Print the search menu
	menu_header("Search Contact by: ");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
	printf("Please select an option: ");

	//Get option from user
	option = checkIntChar();

	//Choose function to run based on the the user selection
	switch(option) {
		//If option is 0, go back main menu
		case e_first_opt: return e_back;
		//If option is 1, search the name in contact
		//If the name exists, display all of them
		//If not, print a warning message
		case e_second_opt: 
			printf("Enter the Name: ");
			scanf("%s",&strInput);
			return displayByName(address_book,strInput);
		//If option is 2, search the phone number in contact
		//if the phone exists, display all of them
		//If not, print a warning message
		case e_third_opt:
			printf("Enter a phone number: ");
			scanf("%s",&strInput);
			return displayByPhone(address_book,strInput);
		//If option is 3, search the email number in contact
		//if the email exists, display all of them
		//If not, print a warning message
		case e_fourth_opt:
			printf("Enter an email: ");
			scanf("%s",&strInput);
			return displayByEmail(address_book,strInput);
		//If option is 4, search the serial number in contact
		//if the serial number exists, display it
		//If not, print a warning message
		case e_fifth_opt:
			printf("Enter serial number: ");
			serialNumber = checkIntChar();
			return displayBySerial(address_book,serialNumber);
		//If option is something else, exit the search_contact
		default: 
			printf("Invalid input\n");
			return e_fail;
	}
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	//Have to find out some way to be able to search the contact first
	search_contact(address_book);
	int rememberIndex;
	printf("Please enter the si number of the contact you would like to edit: ");
	scanf("%d", &rememberIndex);
	rememberIndex -= 1; //To be the same value as the index
	int editInput;

	while(editInput != 0) //looping so that user can keep editing many times using the menu
	{
		printf("0. Exit\n");
		printf("1. Edit by name\n");
		printf("2. Edit by phone number\n");
		printf("3. Edit by email\n");
		printf("\n");
		printf("Please select an option: ");
		scanf("%d", &editInput);
		int allOrSpecificInput;
		
		if(editInput == 1) //by name
		{	
			printf("Current name is %s\n", address_book -> list[rememberIndex].name[0]);
			printf("Please enter new name: ");
			scanf("%s", &address_book -> list[rememberIndex].name[0]);
			printf("\n");
		}
		else if(editInput == 2)//by phone number
		{	
			printf("Would you like to edit all the phone numbers or just a specific one? Enter 1 to edit all, enter");
			printf(" 2 to edit a specific one: ");
			scanf("%d", &allOrSpecificInput);
			printf("\n");
			if (allOrSpecificInput == 1) //editing all the phone numbers
			{
				for(int phoneIndex = 0; phoneIndex < PHONE_NUMBER_COUNT; phoneIndex++)
				{
					printf("Current phone number is %s\n", address_book -> list[rememberIndex].phone_numbers[phoneIndex]);
					printf("Please enter new phone number: ");
					scanf("%s", &address_book -> list[rememberIndex].phone_numbers[phoneIndex]);
					printf("\n");
				}
			}
			else //editing a specific phone number entry
			{
				char phoneCheck[30];
				printf("Please enter which specific phone number you would like to change: ");
				scanf("%s", &phoneCheck);
				for(int phoneIndex = 0; phoneIndex < PHONE_NUMBER_COUNT; phoneIndex++)
				{
					if(strcmp(phoneCheck, address_book -> list[rememberIndex].phone_numbers[phoneIndex]) == 0)
					{
						printf("Please enter new phone number: ");
						scanf("%s", &address_book -> list[rememberIndex].phone_numbers[phoneIndex]);
						printf("\n");
						phoneIndex = (PHONE_NUMBER_COUNT - 1); //ending as soon as you change
					}
					else if((phoneIndex == (PHONE_NUMBER_COUNT - 1)) && 
						strcmp(phoneCheck, address_book -> list[rememberIndex].phone_numbers[phoneIndex]) != 0) /*If we didn't find 
																												the number to change*/
					{
						printf("Phone number not found you will be brought back to the main menu.\n");
					}
				}

			}
		}
		else if(editInput == 3) //by email
		{	
			printf("Would you like to edit all the email or just a specific one? Enter 1 to edit all, enter");
			printf(" 2 to edit a specific one: ");
			scanf("%d", &allOrSpecificInput);
			printf("\n");
			if (allOrSpecificInput == 1) //editing all the emails
			{
				for(int emailIndex = 0; emailIndex < EMAIL_ID_COUNT; emailIndex++)
				{
					printf("Current email is %s\n", address_book -> list[rememberIndex].email_addresses[emailIndex]);
					printf("Please enter new email: ");
					scanf("%s", &address_book -> list[rememberIndex].email_addresses[emailIndex]);
					printf("\n");
				}
			}
			else //editing a specific email entry
			{
				char emailCheck[30];
				printf("Please enter which email you would like to change: ");
				scanf("%s", &emailCheck);
				for(int emailIndex = 0; emailIndex < EMAIL_ID_COUNT; emailIndex++)
				{
					if(strcmp(emailCheck, address_book -> list[rememberIndex].email_addresses[emailIndex]) == 0)
					{
						printf("Please enter new email: ");
						scanf("%s", &address_book -> list[rememberIndex].email_addresses[emailIndex]);
						printf("\n");
						emailIndex = (EMAIL_ID_COUNT - 1); //ending as soon as you edit
					}
					else if((emailIndex == (EMAIL_ID_COUNT - 1)) && 
						strcmp(emailCheck, address_book -> list[rememberIndex].email_addresses[emailIndex]) != 0) /*If we didn't find 
																												the email to change*/
					{
						printf("Email not found you will be brought back to the main menu.\n");
					}
				}

			}
		}
	}
	return e_success; //I think this allows the information to be saved
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}

void displayList(AddressBook *address_book) {
	list_header();
	for(int j = 0; j < address_book->count;j++) {
		list_content(address_book, &j);
	}
}

void displayContact(AddressBook *address_book, int * index) {
	list_header();
	list_content(address_book, index);
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

Status displayByName(AddressBook * address_book, const char * name) 
{
	bool exist = false;
	for(int i = 0; i < address_book->count; i++) {
		if(strcmp(name,address_book->list[i].name[0]) == 0) {
			if(exist == false) {
				list_header();
				exist = true;
			}

			list_content(address_book,&i);
		}
	}

	if(exist == true) {
		return e_success;
	}
	else {
		printf("No match!\n");
		return e_fail;
	}
}

Status displayByPhone(AddressBook * address_book, const char * phone) {
	bool exist = false;
	for(int i = 0; i < address_book->count; i++) {
		for(int j = 0; j < PHONE_NUMBER_COUNT; j++) {
			if(strcmp(phone, address_book->list[i].phone_numbers[j]) == 0) {
				if(exist == false) {
					list_header();	
					exist = true;
				}

				list_content(address_book,&i);
				break;
			}
		}
	}

	if(exist == true) {
		return e_success;
	}
	else {
		printf("No match!\n");
		return e_fail;
	}
}

Status displayByEmail(AddressBook * address_book, const char * email) 
{
	bool exist = false;
	for(int i = 0; i < address_book->count; i++) {
		for(int j = 0; j < EMAIL_ID_COUNT; j++) {
			if(strcmp(email, address_book->list[i].email_addresses[j]) == 0) {
				if(exist == false) {
					list_header();		
					exist = true;
				}

				list_content(address_book,&i);
				break;
			}
		}
	}

	if(exist == true) {
		return e_success;
	}
	else {
		printf("No match!\n");
		return e_fail;
	}
}

Status displayBySerial(AddressBook * address_book, int serialNumber) 
{
	int index = 0;
	bool exist = false;
	
	if(serialNumber > 0 && serialNumber <= address_book->count) {
		list_header();
		index = serialNumber - 1;
		list_content(address_book, &index );
		exist = true;
	}

	if(exist == true) {
		return e_success;
	}
	else {
		printf("No match!\n");
		return e_fail;
	}
}

void list_header() 
{
	printf("=================================================================================================================\n");
	printf("%c %-10s %c %-30s %c %-30s %c %-30s %c\n",':',"S.No",':', "Name", ':', "Phone No", ':', "Email ID",':');
	printf("=================================================================================================================\n");
}

void list_content(AddressBook * address_book, int * index) 
{
	printf("%c %-10d %c %-30s %c %-30s %c %-30s %c\n",':',address_book->list[*index].si_no,':', address_book->list[*index].name[0], ':', (strcmp(address_book->list[*index].phone_numbers[0],"[empty]") == 0 ? "" : address_book->list[*index].phone_numbers[0]), ':', strcmp(address_book->list[*index].email_addresses[0],"[empty]") == 0 ? "" : address_book->list[*index].email_addresses[0], ':');
	for(int j = 1; j < PHONE_NUMBER_COUNT; j++) {
		printf("%c %-10s %c %-30s %c %-30s %c %-30s %c\n",':',"",':', "", ':', ((strcmp(address_book->list[*index].phone_numbers[j],"[empty]") == 0) ? "" : address_book->list[*index].phone_numbers[j]), ':', ((strcmp(address_book->list[*index].email_addresses[j],"[empty]") == 0) ? "" : address_book->list[*index].email_addresses[j]),':');
	}
	printf("=================================================================================================================\n");
}
