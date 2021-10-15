#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book, int size)
{
	//Initialization
	for(int i = 0; i < size ;i++) {
		address_book->list[i].si_no = 0;
		strcpy(address_book->list[i].name[0],"[empty]");
		for(int j = 0; j < PHONE_NUMBER_COUNT; j++) {
			strcpy(address_book->list[i].phone_numbers[j],"[empty]");
			strcpy(address_book->list[i].email_addresses[j],"[empty]");
		}
	}
	
	//Check for file existance, if the file exists, return 0
	int ret = access(DEFAULT_FILE,F_OK);

	//If file exists
	if (ret == 0)
	{
		//Open the file
		address_book->fp = fopen(DEFAULT_FILE,"a+");

		//If can not open the file, return e_fail
		if(address_book->fp == NULL) {
			return e_fail;
		}
		//If can open the file
		else {
			//Initialization
			int row = 0, col = 0;
			char buffer[225];

			while(fgets(buffer,225,address_book->fp)) {
				col = 1;
				row++;

				char * value = strtok(buffer, ", \n");

				while(value) {
					if(col == 1) {
						address_book->list[row-1].si_no = (*value - '0'); 
					}						
					else if (col == 2)
					{
						strcpy(address_book->list[row-1].name[0],value);
					}						
					else if (col >= 3 && col <= 7)
					{
						strcpy(address_book->list[row-1].phone_numbers[col - 3],value);
					}
					else if (col >= 8 && col <= 12){
						strcpy(address_book->list[row-1].email_addresses[col - 8],value);
					}

					value = strtok(NULL,", \n");
					col++;
				}
			}
			address_book->count = row;
		}
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE,"r");
		address_book->count = 0;
	}

	fclose(address_book->fp);

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */
	for(int i = 0; i < address_book->count; i++) {
		fprintf(address_book->fp,"%d, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",address_book->list[i].si_no, address_book->list[i].name[0],
			address_book->list[i].phone_numbers[0], address_book->list[i].phone_numbers[1], address_book->list[i].phone_numbers[2], address_book->list[i].phone_numbers[3],
			address_book->list[i].phone_numbers[4],address_book->list[i].email_addresses[0],address_book->list[i].email_addresses[1],address_book->list[i].email_addresses[2],
			address_book->list[i].email_addresses[3],address_book->list[i].email_addresses[4]);
	}
	

	fclose(address_book->fp);

	return e_success;
}
