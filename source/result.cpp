#include <curses.h>
#include "result.h"
#include "semester.h"
#include "student.h"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

Result::Result(WINDOW** data, WINDOW** first, WINDOW** sec, WINDOW** pWin, WINDOW** aWin)
{
    dataWin = data;
    firstWin = first;
    secWin = sec;
    personalWin = pWin;
    academicWin = aWin;
}


void Result::set_semNums()
{
    while (1)
    {
        mvwprintw(*dataWin, 1, 0, "Enter number of semesters (1-8): ");
        wrefresh(*dataWin);
        semNums = input_int();
        mvwprintw(*dataWin, 1, 0, "                                     ");
        if (semNums <= 8 && semNums >= 1)
        {
            break;
        }
        else {
            mvwprintw(*dataWin, 1, 0, "Invalid semester number!");
            beep();
            wrefresh(*dataWin);
            napms(2000);
        }
    }
}

void Result::set_data()
{
    for (int i = 0; i < semNums; i++)
    {
        sm[i].set_win(dataWin, firstWin, secWin);
        sm[i].set_sem_num(i + 1);
        sm[i].clean_sem_win(i + 1, sm[i - 1]);
        sm[i].set_num_of_courses(i + 1);
        sm[i].set_course_print(i + 1);
    }
}

void Result::set_student_info()
{
    stu.set_win(dataWin, personalWin, academicWin);
    stu.set_push_personal_info();
    stu.set_push_acad_info();
}

void Result::make_file()
{
    std::string fileName = std::to_string(stu.get_rollNo_for_filenam()) + ".txt";
    ofstream fout;

    int lineWidth = 130;
    // Calculate padding
    string text = "| University of the Punjab |";
    int padding = (lineWidth - text.length()) / 2;

    fout.open(fileName);
    string leadingSpaces(padding, ' ');
    fout << leadingSpaces << "----------------------------" << endl;
    fout << leadingSpaces << text << endl;
    fout << leadingSpaces << "----------------------------" << endl;
    for (int i = 0; i < semNums; i++)
    {
        fout << "Semester " << i + 1 << ":" << endl << endl;
        fout << left
            << setw(12) << "Course Code"
            << setw(30) << "Course Title"
            << setw(12) << "Marks-Obt"
            << setw(6) << "CH"
            << setw(10) << "Grade"
            << setw(14) << "Grade-Points"
            << endl;
        fout << string(90, '-') << endl;

        for (int j = 0; j < sm[i].num_of_courses; j++)
        {
            fout << left
                << setw(12) << sm[i].c[j].cCode
                << setw(30) << sm[i].c[j].cTitle
                << setw(12) << sm[i].c[j].marksObt
                << setw(6) << sm[i].c[j].chHour
                << setw(10) << sm[i].c[j].grade
                << setw(14) << sm[i].c[j].gradePoints
                << endl;
        }
        fout << endl;
    }
    fout.close();
    mvwprintw(*dataWin, 1, 0, "Your file has been successfully saved using your roll number as the filename.");
    wrefresh(*dataWin);
    napms(5000);
    mvwprintw(*dataWin, 1, 0, "                                                                              ");
    wrefresh(*dataWin);
}

void Result::get_file()
{
    string line;
    std::string fileName = std::to_string(stu.get_rollNo_for_filenam()) + ".txt";
    ifstream fin;
    fin.open(fileName);
    while (fin)
    {
        getline(fin, line);
        printw("%s\n", line.c_str());
    }
    fin.close();
}


int Result::input_int()
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