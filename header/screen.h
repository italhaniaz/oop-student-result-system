#pragma once

class Screens {
private:
	char stuName[55];
	char fathName[55];
	char academSec[10];
	char regNum[15];
	char rollNo[12];
public:
	//		Screens();
	void welcomeScreen();
	// Home screen
	int homeScreen();
	void userGuide();
	void student_results_screen();
	void centerSlow(int row, const char* title);
	void slow(const char* line);
	void loadingScreen();
	void centerSlowLoading(int row, const char* title);
	void slowLoading(const char* line);
	void center(int row, const char* title);
	void drawHomeItem(int item);
};

