#include <iostream>

#include "Everything.h"

int main() {
	// Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// Default Console Color (red)
	std::cout << "\u001b[31m";

	// Creating user object
	User user;

	// Calling welcome function
	user.welcome();
	// Lets program until exit code
	while (1);

	return 0;
}