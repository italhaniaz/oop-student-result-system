#pragma once
#include <curses.h>
#include "course.h"

class Semester
{
public:
    int semNum;
    WINDOW** semdataWin;
    WINDOW** semfirstWin;
    WINDOW** semsecWin;
    int num_of_courses;
public:
    Semester();
    Course c[6];
    void set_win(WINDOW** semdata, WINDOW** semfirst, WINDOW** semsec);
    void set_sem_num(int s);
    void clean_sem_win(int s, Semester& prevSem);
    void set_num_of_courses(int s);
    void set_course_print(int s);
    int get_num_courses();
    int input_int();
};

