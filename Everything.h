#ifndef BOOKINGMADEBETTER_EVERYTHING_H
#define BOOKINGMADEBETTER_EVERYTHING_H

#include <vector>

#include <iostream>

#include <ctime>

// Ansi codes
/*
#define clear "\x1B[2J\x1B["
#define red "\u001b[31m"
#define cyan "\u001b[36m"
#define green "\u001b[32m";
#define magenta "\u001b[35m"
#define yellow "\u001b[33m";
*/


// User class
class User {

private:
	// Init private variables
	std::string username;
	std::string email;
	std::string password;
	bool isStudent = true;
	bool isLoggedIn = false;
	int id;
	int count;
	bool has;


public:
	// Init public variablies
	int in;
	std::string inStr;
	std::string room;
	std::string time;
	double timeStart;
	double timeEnd;
	double max;

	// Init private functions
	void welcome();
	void signup();
	void loginInfo();
	void login(std::string tempUsername, std::string tempPassword);

	void portal();
	void chromebookCheckout();
	void chromebookCheckin();

	void studyRooms();
};

// Constructor & destructor 
// User();
// virtual  ~ User();

#endif