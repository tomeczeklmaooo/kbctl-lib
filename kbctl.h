#ifndef KBCTL_H
#define KBCTL_H

typedef struct menu_option
{
	char *label;
	void (*action)(void);
} menu_option;

typedef struct menu
{
	char *title;
	menu_option *options;
	int option_count;
} menu;

void start_menu(menu *menu);

#endif /* KBCTL_H */