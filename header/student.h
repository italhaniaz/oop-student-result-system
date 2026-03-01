#pragma once
#include <curses.h>

class Student
{
private:

    WINDOW** dataWin;
    WINDOW** presonalInfoWin;
    WINDOW** acadInfoWin;
    // Personal information attributes
    std::string degPrg;
    std::string firstName;
    std::string lastName;
    std::string institute;
    // Acadmic infromarion attributes
    int duration;
    std::string acadSec;
    std::string uniReg;
    int rollNo;
    std::string examType;
public:
    int get_rollNo_for_filenam();
    void set_win(WINDOW** dwin, WINDOW** personalwin, WINDOW** acadwin);
    void set_push_personal_info();
    void set_push_acad_info();
    std::string input_str();
    int input_int();
};

