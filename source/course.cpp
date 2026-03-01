#include "course.h"
#include <curses.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;


Course::Course()
{
	cCode[0] = '\0';
	cTitle[0] = '\0';
	grade[0] = '\0';
	marksObt = 0;
	chHour = 0;
	gradePoints = 0;
}

void Course::set_windows_by_sem(WINDOW** cdatawin, WINDOW** csem1Win, WINDOW** csem2win)
{
	printing = cdatawin;
	sem1printing = csem1Win;
	sem2printing = csem2win;
}


void Course::setcCode()
{
	mvwprintw(*printing, 1, 0, "Enter the course code: ");
	wrefresh(*printing);
	cCode = input_str();
	mvwprintw(*printing, 1, 0, "                                  ");
	wrefresh(*printing);
}

void Course::setchHour()
{
	while (1)
	{
		mvwprintw(*printing, 1, 0, "Enter the CH hours: ");
		wrefresh(*printing);
		chHour = input_flt();
		mvwprintw(*printing, 1, 0, "                                      ");
		wrefresh(*printing);
		if (chHour <= 4.000 && chHour >= 2.000)
		{
			break;
		}
		else
		{
			mvwprintw(*printing, 1, 0, "Invalid input!");
			beep();
			wrefresh(*printing);
			napms(2000);
		}
	}

}

void Course::setcTitle()
{
	mvwprintw(*printing, 1, 0, "Enter the title: ");
	wrefresh(*printing);
	cTitle = input_str();
	mvwprintw(*printing, 1, 0, "                                             ");
	wrefresh(*printing);
}

void Course::setgrade()
{
	//while (1)
	//{
	//	mvwprintw(*printing, 1, 0, "Enter the grade(A-F): ");
	//	wrefresh(*printing);
	//	wgetstr(*printing, grade);
	//	mvwprintw(*printing, 1, 0, "                                      ");
	//	wrefresh(*printing);
	//	if (grade[0] <= 'F' && grade[0] >= 'A')
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		mvwprintw(*printing, 1, 0, "Invalid input!");
	//		beep();
	//		wrefresh(*printing);
	//		napms(2000);
	//	}
	//}
	if (marksObt >= 90)
	{
		grade[0] = 'A';
		grade[1] = '+';
		grade[2] = '\0';
	}
	else if (marksObt >= 80)
	{
		grade[0] = 'A';
		grade[1] = '\0';
	}
	else if (marksObt >= 75)
	{
		grade[0] = 'B';
		grade[1] = '+';
		grade[2] = '\0';
	}
	else if (marksObt >= 70)
	{
		grade[0] = 'B';
		grade[1] = '\0';
	}
	else if (marksObt >= 65)
	{
		grade[0] = 'C';
		grade[1] = '+';
		grade[2] = '\0';
	}
	else if (marksObt >= 60)
	{
		grade[0] = 'C';
		grade[1] = '\0';
	}
	else if (marksObt >= 55)
	{
		grade[0] = 'D';
		grade[1] = '+';
		grade[2] = '\0';
	}
	else if (marksObt >= 50)
	{
		grade[0] = 'D';
		grade[1] = '\0';
	}
	else
	{
		grade[0] = 'F';
		grade[1] = '\0';
	}
}

void Course::setgradePoints()
{/*
	while (1)
	{
		mvwprintw(*printing, 1, 0, "Enter the grade points: ");
		wrefresh(*printing);
		wscanw(*printing, "%f", &gradePoints);
		mvwprintw(*printing, 1, 0, "                                      ");
		wrefresh(*printing);
		if (gradePoints <= 4.000 && gradePoints >= 0.000)
		{
			break;
		}
		else
		{
			mvwprintw(*printing, 1, 0, "Invalid input!");
			beep();
			wrefresh(*printing);
			napms(2000);
		}
	}*/
	if (marksObt >= 86)
	{
		gradePoints = 4;
	}
	else if (marksObt >= 82)
	{
		gradePoints = 3.67;
	}
	else if (marksObt >= 78)
	{
		gradePoints = 3.33;
	}
	else if (marksObt >= 74)
	{
		gradePoints = 3;
	}
	else if (marksObt >= 70)
	{
		gradePoints = 2.67;
	}
	else if (marksObt >= 66)
	{
		gradePoints = 2.33;
	}
	else if (marksObt >= 62)
	{
		gradePoints = 2;
	}
	else if (marksObt >= 58)
	{
		gradePoints = 1.67;
	}
	else if (marksObt >= 54)
	{
		gradePoints = 1.33;
	}
	else if (marksObt >= 50)
	{
		gradePoints = 1.20;
	}
	else if (marksObt >= 20)
	{
		gradePoints = 1;
	}
	else
	{
		gradePoints = 0;
	}
}

void Course::setmarksObt()
{
	while (1) {
		mvwprintw(*printing, 1, 0, "Enter the marks(1-100): ");
		wrefresh(*printing);
		marksObt = input_flt();
		mvwprintw(*printing, 1, 0, "                                      ");
		wrefresh(*printing);
		if (marksObt <= 100 && marksObt >= 0) {
			break;
		}
		else {
			mvwprintw(*printing, 1, 0, "Invalid input!");
			beep();
			wrefresh(*printing);
			napms(2000);
		}
	}

}

void Course::setAll()
{
	setcCode();
	setcTitle();
	setmarksObt();
	setchHour();
	setgrade();
	setgradePoints();
}

void Course::push_to_sem1(int i) {
	wattrset(*sem1printing, A_BOLD);
	mvwprintw(*sem1printing, i + 2, 1, "%s", cCode.c_str());
	mvwprintw(*sem1printing, i + 2, 12, "%s", cTitle.c_str());
	mvwprintw(*sem1printing, i + 2, 38, "%.2f", marksObt);
	mvwprintw(*sem1printing, i + 2, 52, "%.2f", chHour);
	mvwprintw(*sem1printing, i + 2, 58, "%s", grade);
	mvwprintw(*sem1printing, i + 2, 65, "%.2f", gradePoints);
	wattroff(*sem1printing, A_BOLD);
	wrefresh(*sem1printing);
}

void Course::push_to_sem2(int i) {
	wattrset(*sem2printing, A_BOLD);
	mvwprintw(*sem2printing, i + 2, 1, "%s", cCode.c_str());
	mvwprintw(*sem2printing, i + 2, 12, "%s", cTitle.c_str());
	mvwprintw(*sem2printing, i + 2, 38, "%.2f", marksObt);
	mvwprintw(*sem2printing, i + 2, 52, "%.2f", chHour);
	mvwprintw(*sem2printing, i + 2, 58, "%s", grade);
	mvwprintw(*sem2printing, i + 2, 65, "%.2f", gradePoints);
	wattroff(*sem2printing, A_BOLD);
	wrefresh(*sem2printing);
}

std::string  Course::input_str()
{
	cbreak();
	noecho();
	keypad(*printing, TRUE);
	char buffer[155];

	int ch;
	int i = 0;
	while (true)
	{
		ch = wgetch(*printing);
		if (ch == '\n' || ch == '\r' || ch == KEY_ENTER)
		{
			break; // exit the loop
		}
		else if (ch == 17)
		{
			endwin();
			exit(0);
		}
		else if (ch == '\b' && i > 0)
		{
			wprintw(*printing, "\b \b");
			wrefresh(*printing);
			buffer[i - 1] = '\0';
			i--;
		}
		else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == 32 || ch == 45 || (ch >= '0' && ch <= '9'))
		{
			waddch(*printing, ch);
			wrefresh(*printing);
			buffer[i++] = ch;

		}
	}
	buffer[i] = '\0';
	std::string passBack(buffer);
	return passBack;
}

float  Course::input_flt()
{
	cbreak();
	noecho();
	keypad(*printing, TRUE);
	char buffer[155];

	int ch;
	int i = 0;
	while (true)
	{
		ch = wgetch(*printing);
		if (ch == '\n' || ch == '\r' || ch == KEY_ENTER)
		{
			break; // exit the loop
		}
		else if (ch == 17)
		{
			endwin();
			exit(0);
		}
		else if (ch == '\b' && i > 0)
		{
			wprintw(*printing, "\b \b");
			wrefresh(*printing);
			buffer[i - 1] = '\0';
			i--;
		}
		else if (ch == 32 || ch == 45 || ch == 46 || (ch >= '0' && ch <= '9'))
		{
			waddch(*printing, ch);
			wrefresh(*printing);
			buffer[i++] = ch;

		}
	}
	buffer[i] = '\0';
	if (buffer[0] == '\0')
	{
		return 0.0;
	}
	float  returnVal = stof(buffer);
	return returnVal;
}

