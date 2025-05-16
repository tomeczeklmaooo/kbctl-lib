#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "kbctl.h"

static void set_raw_mode(int enabled)
{
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	if (enabled)
		tty.c_lflag &= ~(ICANON | ECHO);
	else
		tty.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}

void start_menu(menu *menu)
{
	int selected_option = 0;
	set_raw_mode(1);

	while (1)
	{
		printf("\033c");
		printf("%s\n\n", menu->title);

		for (int i = 0; i < menu->option_count; i++)
		{
			if (i == selected_option)
				printf("\033[7m%s\033[27m\n", menu->options[i].label);
			else
				printf("\033[27m%s\n", menu->options[i].label);
		}

		int c = getchar();

		if (c == 27)
		{
			getchar();

			switch (getchar())
			{
				case 'A':
					if (selected_option > 0) selected_option--;
					break;
				case 'B':
					if (selected_option < menu->option_count - 1) selected_option++;
					break;
			}
		}
		else if (c == '\n')
		{
			set_raw_mode(0);
			printf("\033c");
			menu->options[selected_option].action();
			break;
		}
	}

	set_raw_mode(0);
}