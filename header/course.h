#include<string>
#include<curses.h>
#pragma once

class Course
{
private:
    WINDOW** printing;
    WINDOW** sem1printing;
    WINDOW** sem2printing;
public:
    std::string cCode;
    std::string cTitle;
    float marksObt;
    float chHour;
    char grade[3];
    float gradePoints;
    Course();
    void setcCode();
    void setcTitle();
    void setmarksObt();
    void setchHour();
    void setgrade();
    void setgradePoints();
    void setAll();
    void set_windows_by_sem(WINDOW** cdatawin, WINDOW** csem1Win, WINDOW** csem2win);
    void push_to_sem1(int i);
    std::string input_str();
    float  input_flt();
    void push_to_sem2(int i);
};
