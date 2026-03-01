#include <curses.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "student.h"

void Student::set_win(WINDOW** dwin, WINDOW** personalwin, WINDOW** acadwin)
{
    dataWin = dwin;
    presonalInfoWin = personalwin;
    acadInfoWin = acadwin;
    rollNo = 0;
    duration = 0;
}



void Student::set_push_personal_info()
{



    mvwprintw(*dataWin, 1, 0, "Please enter your personal info here.");
    wrefresh(*dataWin);
    napms(2000);
    mvwprintw(*dataWin, 1, 0, "                                     ");


    // this is starting 1 input and printing
    mvwprintw(*dataWin, 1, 0, "Enter your degree programe: ");
    wrefresh(*dataWin);
    degPrg = input_str();

    wattrset(*presonalInfoWin, A_BOLD);
    mvwprintw(*presonalInfoWin, 0, 16, "%s", degPrg.c_str());
    wattroff(*presonalInfoWin, A_BOLD);

    wrefresh(*presonalInfoWin);

    mvwprintw(*dataWin, 1, 0, "                                                                                 ");
    wrefresh(*dataWin);
    // this is ending 1 input and priniting

    mvwprintw(*dataWin, 1, 0, "Enter student name: ");
    wrefresh(*dataWin);
    firstName = input_str();

    wattrset(*presonalInfoWin, A_BOLD);
    mvwprintw(*presonalInfoWin, 1, 14, "%s", firstName.c_str());
    wattroff(*presonalInfoWin, A_BOLD);

    wrefresh(*presonalInfoWin);

    mvwprintw(*dataWin, 1, 0, "                                                ");
    wrefresh(*dataWin);



    mvwprintw(*dataWin, 1, 0, "Enter father name: ");
    wrefresh(*dataWin);
    lastName = input_str();

    wattrset(*presonalInfoWin, A_BOLD);
    mvwprintw(*presonalInfoWin, 2, 13, "%s", lastName.c_str());
    wattroff(*presonalInfoWin, A_BOLD);

    wrefresh(*presonalInfoWin);


    mvwprintw(*dataWin, 1, 0, "                                                ");
    wrefresh(*dataWin);


    mvwprintw(*dataWin, 1, 0, "Enter name of your institute: ");
    wrefresh(*dataWin);
    institute = input_str();

    wattrset(*presonalInfoWin, A_BOLD);
    mvwprintw(*presonalInfoWin, 3, 11, "%s", institute.c_str());
    wattroff(*presonalInfoWin, A_BOLD);

    wrefresh(*presonalInfoWin);

    mvwprintw(*dataWin, 1, 0, "                                                                                            ");
    wrefresh(*dataWin);
}

void Student::set_push_acad_info()
{
    mvwprintw(*dataWin, 1, 0, "Please enter your academic info here.");
    wrefresh(*dataWin);
    napms(2000);
    mvwprintw(*dataWin, 1, 0, "                                     ");

    mvwprintw(*dataWin, 1, 0, "Enter the year num of duration(1-4): ");
    wrefresh(*dataWin);
    duration = input_int();

    wattrset(*acadInfoWin, A_BOLD);
    mvwprintw(*acadInfoWin, 0, 10, "%d Years", duration);
    wattroff(*acadInfoWin, A_BOLD);

    wrefresh(*acadInfoWin);

    mvwprintw(*dataWin, 1, 0, "                                                ");
    wrefresh(*dataWin);



    mvwprintw(*dataWin, 1, 0, "Enter the academic section e.g(2024-28): ");
    wrefresh(*dataWin);
    acadSec = input_str();

    wattrset(*acadInfoWin, A_BOLD);
    mvwprintw(*acadInfoWin, 1, 17, "%s", acadSec.c_str());
    wattroff(*acadInfoWin, A_BOLD);

    wrefresh(*acadInfoWin);


    mvwprintw(*dataWin, 1, 0, "                                                        ");
    wrefresh(*dataWin);


    mvwprintw(*dataWin, 1, 0, "Enter the university regestratin num: ");
    wrefresh(*dataWin);
    uniReg = input_str();

    wattrset(*acadInfoWin, A_BOLD);
    mvwprintw(*acadInfoWin, 2, 19, "%s", uniReg.c_str());
    wattroff(*acadInfoWin, A_BOLD);

    wrefresh(*acadInfoWin);


    mvwprintw(*dataWin, 1, 0, "                                                                   ");
    wrefresh(*dataWin);



    mvwprintw(*dataWin, 1, 0, "Enter the rollno: ");
    wrefresh(*dataWin);
    rollNo = input_int();

    wattrset(*acadInfoWin, A_BOLD);
    mvwprintw(*acadInfoWin, 3, 9, "%d", rollNo);
    wattroff(*acadInfoWin, A_BOLD);

    wrefresh(*acadInfoWin);



    mvwprintw(*dataWin, 1, 0, "                                                ");
    wrefresh(*dataWin);


    mvwprintw(*dataWin, 1, 0, "Enter the exam type: ");
    wrefresh(*dataWin);
    examType = input_str();


    wattrset(*acadInfoWin, A_BOLD);
    mvwprintw(*acadInfoWin, 4, 11, "%s", examType.c_str());
    wattroff(*acadInfoWin, A_BOLD);

    wrefresh(*acadInfoWin);


    mvwprintw(*dataWin, 1, 0, "                                                ");
    wrefresh(*dataWin);

}

int Student::get_rollNo_for_filenam()
{
    return rollNo;
}


std::string  Student::input_str()
{
    cbreak();
    noecho();
    keypad(*dataWin, TRUE);
    char buffer[155];

    int ch;
    int i = 0;
    while (true)
    {
        ch = wgetch(*dataWin);
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
            wprintw(*dataWin, "\b \b");
            wrefresh(*dataWin);
            buffer[i - 1] = '\0';
            i--;
        }
        else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == 32 || ch == 45 || (ch >= '0' && ch <= '9'))
        {
            waddch(*dataWin, ch);
            wrefresh(*dataWin);
            buffer[i++] = ch;

        }
    }
    buffer[i] = '\0';
    std::string passBack(buffer);
    return passBack;
}


int Student::input_int()
{
    cbreak();
    noecho();
    keypad(*dataWin, TRUE);
    char buffer[155];

    int ch;
    int i = 0;
    while (true)
    {
        ch = wgetch(*dataWin);
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
            wprintw(*dataWin, "\b \b");
            wrefresh(*dataWin);
            buffer[i - 1] = '\0';
            i--;
        }
        else if (ch == 32 || ch == 45 || (ch >= '0' && ch <= '9'))
        {
            waddch(*dataWin, ch);
            wrefresh(*dataWin);
            buffer[i++] = ch;

        }
    }
    buffer[i] = '\0';
    if (buffer[0] == '\0')
    {
        return 0;
    }
    int returnVal = std::stoi(buffer);
    return returnVal;
}