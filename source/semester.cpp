#include <stdlib.h>
#include "semester.h"
#include "course.h"
#include "result.h"


Semester::Semester()
{
    semNum = 0;
}

void Semester::set_win(WINDOW** semdata, WINDOW** semfirst, WINDOW** semsec)
{
    semdataWin = semdata;
    semfirstWin = semfirst;
    semsecWin = semsec;
}

void Semester::set_sem_num(int s)
{
    semNum = s;
}

int Semester::get_num_courses()
{
    return num_of_courses;
}


void Semester::clean_sem_win(int s, Semester& prevSem)
{
    start_color();
    init_pair(8, COLOR_BLACK, COLOR_GREEN);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);


    const char* items[] = {
 "First",
 "Second",
 "Third",
 "Fourth",
 "Fifth",
 "Sixth",
 "Seventh",
 "Eight"
    };
    // i acees the semnum means s by -1 for items
    if (s == 1)
    {
        wclear(*semfirstWin);
        wbkgd(*semfirstWin, COLOR_PAIR(1));

        wattrset(*semfirstWin, COLOR_PAIR(8));
        mvwprintw(*semfirstWin, 0, 1, "%s Semester", items[s - 1]);
        wrefresh(*semfirstWin);
        wattroff(*semfirstWin, COLOR_PAIR(8));

        //        wattrset(*d, A_BOLD);
        mvwaddstr(*semfirstWin, 1, 65, "Grade-Points");
        mvwaddstr(*semfirstWin, 1, 58, "Grade");
        mvwaddstr(*semfirstWin, 1, 52, "CH");
        mvwaddstr(*semfirstWin, 1, 38, "Marks Obt.");
        mvwaddstr(*semfirstWin, 1, 12, "Course Title");
        mvwaddstr(*semfirstWin, 1, 1, "C.Code");
        //        wattroff(*d, A_BOLD);
        wrefresh(*semfirstWin);

    }
    else if (s == 2)
    {
        wclear(*semsecWin);

        wbkgd(*semsecWin, COLOR_PAIR(1));

        wattrset(*semsecWin, COLOR_PAIR(8));
        mvwprintw(*semsecWin, 0, 1, "%s Semester", items[s - 1]);
        wrefresh(*semsecWin);
        wattroff(*semsecWin, COLOR_PAIR(8));

        //       wattrset(*e, A_BOLD);
        mvwaddstr(*semsecWin, 1, 65, "Grade-Points");
        mvwaddstr(*semsecWin, 1, 58, "Grade");
        mvwaddstr(*semsecWin, 1, 52, "CH");
        mvwaddstr(*semsecWin, 1, 38, "Marks Obt.");
        mvwaddstr(*semsecWin, 1, 12, "Course Title");
        mvwaddstr(*semsecWin, 1, 1, "C.Code");
        //        wattroff(*e, A_BOLD);

        wrefresh(*semsecWin);
    }

    else if (s > 2)
    {
        wclear(*semfirstWin);
        wclear(*semsecWin);

        // Preparing the previous window.
        wbkgd(*semfirstWin, COLOR_PAIR(1));

        wattrset(*semfirstWin, COLOR_PAIR(8));
        mvwprintw(*semfirstWin, 0, 1, "%s Semester", items[s - 2]);
        wrefresh(*semfirstWin);
        wattroff(*semfirstWin, COLOR_PAIR(8));

        //        wattrset(*d, A_BOLD);
        mvwaddstr(*semfirstWin, 1, 65, "Grade-Points");
        mvwaddstr(*semfirstWin, 1, 58, "Grade");
        mvwaddstr(*semfirstWin, 1, 52, "CH");
        mvwaddstr(*semfirstWin, 1, 38, "Marks Obt.");
        mvwaddstr(*semfirstWin, 1, 12, "Course Title");
        mvwaddstr(*semfirstWin, 1, 1, "C.Code");
        //        wattroff(*d, A_BOLD);
        wrefresh(*semfirstWin);

        for (int i = 0; i < prevSem.get_num_courses(); i++)
        {
            prevSem.c[i].push_to_sem1(i);
        }

        //====================================
        // Reading my third means new window
        //====================================

        wbkgd(*semsecWin, COLOR_PAIR(1));

        wattrset(*semsecWin, COLOR_PAIR(8));
        mvwprintw(*semsecWin, 0, 1, "%s Semester", items[s - 1]);
        wrefresh(*semsecWin);
        wattroff(*semsecWin, COLOR_PAIR(8));

        //       wattrset(*e, A_BOLD);
        mvwaddstr(*semsecWin, 1, 65, "Grade-Points");
        mvwaddstr(*semsecWin, 1, 58, "Grade");
        mvwaddstr(*semsecWin, 1, 52, "CH");
        mvwaddstr(*semsecWin, 1, 38, "Marks Obt.");
        mvwaddstr(*semsecWin, 1, 12, "Course Title");
        mvwaddstr(*semsecWin, 1, 1, "C.Code");
        //        wattroff(*e, A_BOLD);

        wrefresh(*semsecWin);

    }

}


void Semester::set_num_of_courses(int s)
{
    while (1)
    {
        mvwprintw(*semdataWin, 1, 0, "Enter num of courses(max 6) in %d sem: ", s);
        wrefresh(*semdataWin);
        num_of_courses = input_int();
        mvwprintw(*semdataWin, 1, 0, "                                           ");
        wrefresh(*semdataWin);
        if (num_of_courses <= 6 && num_of_courses >= 1) {
            break;
        }
        else {
            mvwprintw(*semdataWin, 1, 0, "Invalid input!");
            beep();
            wrefresh(*semdataWin);
            napms(2000);
        }
    }
}


void Semester::set_course_print(int s)
{
    // c->set_windows_by_sem(semdataWin, semfirstWin, semsecWin);
    for (int i = 0; i < num_of_courses; i++)
    {
        c[i].set_windows_by_sem(semdataWin, semfirstWin, semsecWin);
        if (s == 1) // (s == 1)
        {
            c[i].setAll();
            c[i].push_to_sem1(i);
        }
        else if (s == 2)
        {
            c[i].setAll();
            c[i].push_to_sem2(i);
        }

        else if (s > 2)
        {
            c[i].setAll();
            c[i].push_to_sem2(i);
        }

    }
}

int Semester::input_int()
{
    cbreak();
    noecho();
    keypad(*semdataWin, TRUE);
    char buffer[155];

    int ch;
    int i = 0;
    while (true)
    {
        ch = wgetch(*semdataWin);
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
            wprintw(*semdataWin, "\b \b");
            wrefresh(*semdataWin);
            buffer[i - 1] = '\0';
            i--;
        }
        else if (ch == 32 || ch == 45 || (ch >= '0' && ch <= '9'))
        {
            waddch(*semdataWin, ch);
            wrefresh(*semdataWin);
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