#pragma once
#include <curses.h>
#include "semester.h"
#include "student.h"
#include <string.h>

class Result
{
private:
    int semNums;
    WINDOW** dataWin;
    WINDOW** firstWin;
    WINDOW** secWin;
    WINDOW** personalWin;
    WINDOW** academicWin;
public:
    Result(WINDOW** data, WINDOW** first, WINDOW** sec, WINDOW** pWin, WINDOW** aWin);
    void set_semNums();
    Student stu;
    Semester sm[8];
    void set_student_info();
    void set_data();
    void make_file();
    void get_file();
    int input_int();
};