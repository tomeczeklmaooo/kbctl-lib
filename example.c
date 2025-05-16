#include <stdio.h>

// include the header
#include "kbctl.h"

// some functions that will be called
void do_this() { printf("doing this...\n"); }
void do_that() { printf("doing that...\n"); }

int main()
{
	// define the menu options
	menu_option options[] = {
		{ "Do this", do_this },
		{ "Do that", do_that },
	};

	// define the menu, with title and options array
	menu menu = { "Menu title", options, 2 };

	// finally start the menu
	start_menu(&menu);

	return 0;
}