#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"
#include "screen.h"
#include "result.h"
#include "semester.h"

void bomb(void);
void makeInterface(WINDOW** a, WINDOW** b, WINDOW** c, 
                   WINDOW** d, WINDOW** e, WINDOW** f, 
                   WINDOW** g, int mc, int  mr, int hc,
                   int hr);
void print_static_data(WINDOW** a, WINDOW** b, WINDOW** c,
                       WINDOW** d, WINDOW** e, WINDOW** f,
                       WINDOW** g);
void center(WINDOW* a, int row, char* title);

int main(void)
{
    /* Making the seven windows */
    WINDOW* headerWin, * studentInfoWin, * academicInfoWin,
          * sem1Win, * sem2Win, * dataWin, * designerWin;
    int maxCols, maxRows, halfCols, halfRows, sugession, selectItem;

   initscr();

        /* Making the object of Screens */
        Screens screen;
        screen.welcomeScreen();
        clear();
        screen.loadingScreen();

    while (1)
    {
        clear();
        selectItem = screen.homeScreen();
        clear();

        //=================================
        /* If user wanted to add a record */
        //=================================

        if (selectItem == 1)
        {
            clear();
            screen.loadingScreen();
            /* giving color to the background */
            clear();
            start_color();
            init_pair(1, COLOR_BLACK, COLOR_WHITE);
            bkgd(COLOR_PAIR(1));


            /* calculate window sizes and locations */
            getmaxyx(stdscr, maxRows, maxCols);

            halfCols = maxCols >> 1;
            halfRows = maxRows >> 1;
            refresh();

            /* creating the interface of the software */
            makeInterface(&headerWin, &studentInfoWin, &academicInfoWin, &sem1Win, &sem2Win, &dataWin, &designerWin, maxCols, maxRows, halfCols, halfRows);

            /* Printing the non changing data to the windows */
            print_static_data(&headerWin, &studentInfoWin, &academicInfoWin, &sem1Win, &sem2Win, &dataWin, &designerWin);


            while (1)
            {

                Result r(&dataWin, &sem1Win, &sem2Win, &studentInfoWin, &academicInfoWin);
                r.set_student_info();
                r.set_semNums();
                r.set_data();
                r.make_file();
                //r.get_file();
                //getch();
                /* suggestion for the ending of the programe */

                mvwprintw(dataWin, 1, 0, "Press 1 to continue and 2 for home page ");
                wrefresh(dataWin);
                wscanw(dataWin, "%d", &sugession);

                if (sugession == 2)
                {
                    clear();
                    break;
                }
                else {
                    mvwprintw(dataWin, 1, 0, "                                     ");
                }
            } // this loops break by the sugession 2.
        }
        else if (selectItem == 2)
        {
            clear();
            screen.loadingScreen();
            clear();
            screen.student_results_screen();
            clear();
        }
        else if (selectItem == 3)
        {
            clear();
            screen.loadingScreen();
            clear();
            screen.userGuide();
            clear();
        }
        else if (selectItem == 4)
        {
            endwin();
            return 0;
        }
    }// most outer loop ending    
}





void bomb(void)
{
    addstr("Unable to allocate memory for new window.\n");
    refresh();
    endwin();
    exit(1);
}


void makeInterface(WINDOW** a, WINDOW** b, WINDOW** c, WINDOW** d, WINDOW** e, WINDOW** f, WINDOW** g, int mc, int  mr, int hc, int hr)
{

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    box(stdscr, 0, 0);

    /* header window */
    *a = newwin(1, mc - 2, 1, 1);
    if (*a == NULL) bomb();

    /* Line after the header window */
    move(2, 1);
    hline(ACS_HLINE, mc - 2);

    /* studentInfo window */
    *b = newwin(5, hc + 13, 3, 1); // staring from row 2 and col 1
    if (*b == NULL) bomb();

    /* line between the academic info and the student info */
    move(2, hc + 14);
    vline(ACS_VLINE, 6);

    /* juction of the 4 corners */
    mvaddch(2, 0, ACS_LTEE);
    mvaddch(2, mc - 1, ACS_RTEE);
    mvaddch(8, 0, ACS_LTEE);
    mvaddch(8, mc - 1, ACS_RTEE);

    /* junction phase of this */
    mvaddch(2, hc + 14, ACS_TTEE);


    /* academicInfo Window */
    *c = newwin(5, hc - 16, 3, hc + 15);
    if (*c == NULL) bomb();

    /* line between the semester 1 and the student and the academic info */
    move(8, 1);
    hline(ACS_HLINE, mc - 2);

    /* down junction of acadam and student center one*/
    mvaddch(8, hc + 14, ACS_BTEE); // this is not working // conform this

    /* semester 1 window */
    *d = newwin(8, mc - 2, 9, 1);
    if (*d == NULL) bomb();

    /* semester 2 Window */
    *e = newwin(8, mc - 2, 17, 1);
    if (*e == NULL) bomb();

    /* line between the sem2 and the datawin + designerwin */
    move(25, 1);
    hline(ACS_HLINE, mc - 2);
    /* now the juctions of them*/
    mvaddch(25, 0, ACS_LTEE);
    mvaddch(25, mc - 1, ACS_RTEE);

    /* Data input Window */
    *f = newwin(3, hc + 13, 26, 1);
    if (*f == NULL) bomb();

    /* line betweent he data and the dessingnr win */
    mvaddch(25, hc + 14, ACS_TTEE);
    move(26, hc + 14);
    vline(ACS_VLINE, 3);
    mvaddch(29, hc + 14, ACS_BTEE); // this is not working // conform this


    /* designer window */
    *g = newwin(3, hc - 16, 26, hc + 15);
    if (*g == NULL) bomb();

}

/* This functin center the text of the window one. */
void center(WINDOW* one, int row, const char* title)
{
    int len, indent, y, width;
    getmaxyx(one, y, width);
    len = strlen(title);
    indent = width - len;
    indent /= 2;
    mvwaddstr(one, row, indent, title);
    refresh();
}

void print_static_data(WINDOW** a, WINDOW** b, WINDOW** c, WINDOW** d, WINDOW** e, WINDOW** f, WINDOW** g)
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_BLACK, COLOR_GREEN);


    /* Write to the header window */
    wbkgd(*a, COLOR_PAIR(1));

    center(*a, 0, "University of the Punjab");

    wrefresh(*a);

    /* Writing data to the studentInfo window */
    wbkgd(*b, COLOR_PAIR(1));


    mvwaddstr(*b, 0, 0, "Degree Program: ");
    mvwaddstr(*b, 1, 0, "Student Name: ");
    mvwaddstr(*b, 2, 0, "Father Name: ");
    mvwaddstr(*b, 3, 0, "Institute: ");


    wrefresh(*b);


    wbkgd(*c, COLOR_PAIR(1));

    mvwaddstr(*c, 0, 0, "Duration: ");
    mvwaddstr(*c, 1, 0, "Academic Session: ");
    mvwaddstr(*c, 2, 0, "University Reg.No: \n");
    mvwaddstr(*c, 3, 0, "Roll No: \n");
    mvwaddstr(*c, 4, 0, "Exam Type: ");

    wrefresh(*c);


    /* Writing data to the semester 1 window*/
    wbkgd(*d, COLOR_PAIR(1));

    wattrset(*d, COLOR_PAIR(8));
    mvwaddstr(*d, 0, 1, "First Semester");
    wrefresh(*d);
    wattroff(*d, COLOR_PAIR(8));

    //        wattrset(*d, A_BOLD);
    mvwaddstr(*d, 1, 65, "Grade-Points");
    mvwaddstr(*d, 1, 58, "Grade");
    mvwaddstr(*d, 1, 52, "CH");
    mvwaddstr(*d, 1, 38, "Marks Obt.");
    mvwaddstr(*d, 1, 12, "Course Title");
    mvwaddstr(*d, 1, 1, "C.Code");
    //        wattroff(*d, A_BOLD);
    wrefresh(*d);


    /* Writing data to the semester 2 window */
    wbkgd(*e, COLOR_PAIR(1));

    wattrset(*e, COLOR_PAIR(8));
    mvwaddstr(*e, 0, 1, "Second Semester");
    wrefresh(*e);
    wattroff(*e, COLOR_PAIR(8));

    //       wattrset(*e, A_BOLD);
    mvwaddstr(*e, 1, 65, "Grade-Points");
    mvwaddstr(*e, 1, 58, "Grade");
    mvwaddstr(*e, 1, 52, "CH");
    mvwaddstr(*e, 1, 38, "Marks Obt.");
    mvwaddstr(*e, 1, 12, "Course Title");
    mvwaddstr(*e, 1, 1, "C.Code");
    //        wattroff(*e, A_BOLD);

    wrefresh(*e);


    /* data input window */
    wbkgd(*f, COLOR_PAIR(1));

    mvwaddstr(*f, 0, 0, "Data Input:");

    wrefresh(*f);


    /* dessingner window */
    wbkgd(*g, COLOR_PAIR(1));


    mvwaddstr(*g, 0, 0, "Programmed by: ");
    mvwaddstr(*g, 1, 0, "Version: ");
    mvwaddstr(*g, 2, 0, "Ctrl+Q = Exit\tCtrl+S = Save");


    wattrset(*g, A_BOLD);
    mvwaddstr(*g, 0, 15, "Talha Niaz");
    mvwaddstr(*g, 1, 9, "1.0.0");
    wattroff(*g, A_BOLD);
    wrefresh(*g);

}


