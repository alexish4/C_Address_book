//gcc address_book_fops.h address_book_fops.c address_book_menu.h address_book_menu.c address_book.h main.c
#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

int main(void)
{
	AddressBook address_book;
	Status ret;

	address_book.list = malloc((1000)*sizeof(ContactInfo));

	/* Load the file from .csv file if any */
	ret = load_file(&address_book);

	if (ret == e_success)
	{
		/* Show all the available menu */
		ret = menu(&address_book);

		if (ret == e_success)
		{
			/* Save the entries */
			save_prompt(&address_book);
		}
	}

	free(address_book.list);
	return 0;
}
