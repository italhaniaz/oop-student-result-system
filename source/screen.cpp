#include <curses.h>
#include<stdlib.h>
#include<string.h>
#include "screen.h"
#define HOMEITEM 4

/* This is the main welcome screen for the user. */
void Screens::welcomeScreen()
{
	int mr, mc, hr, hc;
	getmaxyx(stdscr, mr, mc);
	hr = mr / 2;
	hc = mc / 2;
	box(stdscr, 0, 0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));

	// Adding borders on the top and the bottom of my title.
	center((hr - 4), "===============================");
	refresh();
	center((hr), "===============================");
	refresh();
	attrset(COLOR_PAIR(2));
	centerSlow((hr - 2), "STUDENT RESULT MANAGEMENT SYSTEM");
	attroff(COLOR_PAIR(2));
	center((hr + 2), "Press any key to continue");
	refresh();
	getch();
}

/* This is the loading screen */
void Screens::loadingScreen()
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	start_color();

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	/* Setting background color to black */
	bkgd(COLOR_PAIR(1));
	box(stdscr, 0, 0);
	int mr, mc, hr, hc;
	getmaxyx(stdscr, mr, mc);
	hr = mr / 2;
	hc = mc / 2;


	center((hr - 1), "Loading...");
	attrset(COLOR_PAIR(2));
	centerSlowLoading(hr, "[>>>>>>>>>>>>>>>>>>>>>>>>>]");
	attroff(COLOR_PAIR(2));

}

/* This is the Home screen coding */
int Screens::homeScreen()
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	/* Getting the max screensize and breaking it. */
	int mr, mc, hr, hc, key, menuitem = 0;
	getmaxyx(stdscr, mr, mc);
	hr = mr / 2;
	hc = mc / 2;
	box(stdscr, 0, 0);
	center((hr - 11), "===============");
	refresh();
	center((hr - 9), "===============");
	refresh();
	attrset(COLOR_PAIR(2));
	centerSlow((hr - 10), "HOME PAGE");
	attroff(COLOR_PAIR(2));

	/* Drawing the menu for the hoemscreen */
	drawHomeItem(menuitem);
	keypad(stdscr, TRUE);
	noecho();
	/* Disable echo */
	do
	{
		key = getch();
		switch (key)
		{
		case KEY_DOWN:
			menuitem++;
			if (menuitem > HOMEITEM - 1) menuitem = 0;
			break;
		case KEY_UP:
			menuitem--;
			if (menuitem < 0) menuitem = HOMEITEM - 1;
			break;
		default:
			break;
		}
		drawHomeItem(menuitem);
	} while (key != '\n');

	echo();

	/* Checking which option is pressed */
	if (menuitem == 0)
	{
		return 1;
	}
	else if (menuitem == 1)
	{
		return 2;
	}
	else if (menuitem == 2)
	{
		return 3;
	}
	else if (menuitem == 3)
	{
		return 4;
	}
	return 0;
}

/* User Guide manual screen */
void Screens::userGuide()
{
	int mr, mc, hr, hc;
	getmaxyx(stdscr, mr, mc);
	hr = mr / 2;
	hc = mc / 2;

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));
	box(stdscr, 0, 0);

	center(1, "=================");
	refresh();
	center(3, "=================");
	refresh();
	attrset(COLOR_PAIR(2));
	centerSlow(2, "USER GUIDE MANUAL");
	attroff(COLOR_PAIR(2));
	refresh();

	mvaddstr(4, 1, "1. Introduction:");
	//    attrset(A_BOLD);
	mvaddstr(6, 2, "  * This application is designed to manage and maintain student academic results for 1st and 2nd Semester.");
	mvaddstr(7, 2, "  * It allows users to add student records, view stored results, and manage academic data in an organized manner.");
	//    attroff(A_BOLD);

	mvaddstr(9, 1, "2. Navigation Instructions:");
	//    attrset(A_BOLD);
	mvaddstr(11, 2, "  * Use UP and DOWN arrow keys to navigate menu items.");
	mvaddstr(12, 2, "  * Press ENTER to select an option.");
	mvaddstr(13, 2, "  * Press CTRL + Q to exit the application.");
	//    attroff(A_BOLD);

	mvaddstr(15, 1, "3. Home Screen Options:");
	//    attrset(A_BOLD);
	mvaddstr(17, 1, "  > Add Student Record:");
	mvaddstr(18, 1, "	* Allows the user to enter student information and semester-wise results.");
	mvaddstr(19, 1, "  > View Student Results:");
	mvaddstr(20, 1, "	* Displays stored student records for 1st and 2nd semesters.");
	mvaddstr(21, 1, "  > User Guide:");
	mvaddstr(22, 1, "	* Opens the help section describing how to use the application.");
	mvaddstr(23, 1, "  > Exit Application:");
	mvaddstr(24, 1, "	* Closes the program safely.");

	//    attroff(A_BOLD);

	center(27, "Press Enter to go to home page.");
	refresh();
	getch();
}



/* This is the center function */
void Screens::center(int row, const char* title)
{
	int len, indent, y, width;
	getmaxyx(stdscr, y, width);
	len = strlen(title);
	indent = width - len;
	indent /= 2;
	mvaddstr(row, indent, title);
	refresh();
}

/* This is the center for the loading screen */
void Screens::centerSlowLoading(int row, const char* title)
{
	int len, indent, y, width;
	getmaxyx(stdscr, y, width);
	len = strlen(title);
	indent = width - len;
	indent /= 2;
	move(row, indent);
	slowLoading(title);
	refresh();
}

/* This is slow loading for the loading screen */
void Screens::slowLoading(const char* line)
{
	int i = 0;
	while (*line)
	{
		addch(*line);
		line++;
		i++;

		if (i == 8)
		{
			napms(1000);
		}
		else if (i == 21)
		{
			napms(1000);
		}
		else
		{
			napms(30);
		}
		refresh();
	}
}

/* This function center the text + slow it. */
void Screens::centerSlow(int row, const char* title)
{
	int len, indent, y, width;
	getmaxyx(stdscr, y, width);
	len = strlen(title);
	indent = width - len;
	indent /= 2;
	move(row, indent);
	slow(title);
	refresh();
}

void Screens::slow(const char* line)
{
	while (*line)
	{
		addch(*line);
		line++;
		refresh();
		napms(150);
	}
}
/* Ending of the center + slow function */

/* This is the item bar for the home page */
void  Screens::drawHomeItem(int item)
{
	int mr, mc, hr, hc;
	getmaxyx(stdscr, mr, mc);
	hr = mr / 2;
	hc = mc / 2;

	int c;
	char menu[HOMEITEM][21] = {
		/* 4 items for MENUMAX */
		"Add Student Record",
		"View Student Results",
		"User Guide",
		"Exit Application"
	};

	// clear();
	int i[] = { 6, 4, 2, 0 };
	for (c = 0; c < HOMEITEM; c++)
	{
		mvprintw(hr - i[c], 46, "%d.", c + 1);
		if (c == item)
			attron(A_REVERSE);

		center(hr - i[c], menu[c]);
		attroff(A_REVERSE);
	}

	center(hr + 2, "Use arrow keys to move");
	refresh();
}

void Screens::student_results_screen()
{
	int TotalrollNo = 0;
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	/* Getting the max screensize and breaking it. */
	int mr, mc, hr, hc, key, menuitem = 0;
	getmaxyx(stdscr, mr, mc);
	hr = mr / 2;
	hc = mc / 2;
	box(stdscr, 0, 0);
	center(1, "===============");
	refresh();
	center(3, "===============");
	refresh();
	attrset(COLOR_PAIR(2));
	centerSlow(2, "Saved Records");
	attroff(COLOR_PAIR(2));

	/* Drawing the menu for the student_records */
	//drawHomeItem(menuitem);
	//keypad(stdscr, TRUE);
	//noecho();
	///* Disable echo */
	//do
	//{
	//	key = getch();
	//	switch (key)
	//	{
	//	case KEY_DOWN:
	//		menuitem++;
	//		if (menuitem > HOMEITEM - 1) menuitem = 0;
	//		break;
	//	case KEY_UP:
	//		menuitem--;
	//		if (menuitem < 0) menuitem = HOMEITEM - 1;
	//		break;
	//	default:
	//		break;
	//	}
	//	drawHomeItem(menuitem);
	//} while (key != '\n');
	center(27, "Press Enter to go to home page.");
	refresh();
	getch();
}