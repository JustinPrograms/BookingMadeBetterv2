#include "Everything.h"
#include "json.h"
#include <fstream>

using json = nlohmann::json;

void User::welcome() {

	// Welcome prompt
	std::cout << "________________________________\n";
	std::cout << "|            WELCOME           |\n";
	std::cout << "|            TO THE            |\n";
	std::cout << "|            BOOKING           |\n";
	std::cout << "|            SYSTEM            |\n";
	std::cout << "| Mon-Fri (08:00am to 03:00pm) |\n";
	std::cout << "|      1. login 2. signup      |\n";
	std::cout << "--------------------------------\n";

	// Getting input and selecting function
	std::cin >> in;
	std::cout << "\u001b[32m";
	switch (in) {
	case 1:
		std::cout << "\x1B[2J\x1B[H";
		loginInfo();
		break;
	case 2:
		std::cout << "\x1B[2J\x1B[H";
		signup();
		break;
	default:
		std::cout << "\x1B[2J\x1B[H";
		welcome();
	}
}

void User::signup() {


	// Sign up prompt
	std::cout << "______________________________\n";
	std::cout << "|                            |\n";
	std::cout << "|           Sign Up          |\n";
	std::cout << "|                            |\n";
	std::cout << "------------------------------\n";

	// Getting signup information
	std::cout << "Please enter an username: ";
	std::cin >> username;

	std::cout << "Please enter a email address: ";
	std::cin >> email;

	std::cout << "Please enter a password: ";
	std::cin >> password;

	// Reading Json file
	std::ifstream o(R"(D:\Programing\BookingMadeBetter\data\accounts.json)");
	json data = json::parse(o);

	// Adding data
	id = data.size() + 1000;
	data[data.size()] = { {"username", username},
				{"password", password},
				{"email", email},
				{"id", id},
				{"isStudent", isStudent} };

	// Writing to json file
	std::ofstream w("D:\\Programing\\BookingMadeBetter\\data\\accounts.json");
	w << std::setw(4) << data << std::endl;
	w.flush();

	// Auto logging
	login(username, password);
}

void User::loginInfo() {

	std::cout << "\u001b[32m";
	// Login prompt
	std::cout << "______________________________\n";
	std::cout << "|                            |\n";
	std::cout << "|           Login            |\n";
	std::cout << "|                            |\n";
	std::cout << "------------------------------\n";

	// Getting login information
	std::cout << "\nUsername: ";
	std::cin >> username;

	std::cout << "\nPassword: ";
	std::cin >> password;

	// Calling login function
	login(username, password);
}

void User::login(std::string tempUsername, std::string tempPassword) {

	// Reading Json file
	std::ifstream o(R"(D:\Programing\BookingMadeBetter\data\accounts.json)");
	json data = json::parse(o);

	// Checking if valid login information
	for (int i = 0; i < data.size(); i++) {
		if (data[i]["username"] == tempUsername &&
			data[i]["password"] == tempPassword) {

			// If valid gets all the information
			id = static_cast<int>(data[i]["id"]);
			username = data[i]["username"];
			password = data[i]["password"];
			isLoggedIn = true;

			// Calls portal function
			std::cout << "\x1B[2J\x1B[";
			std::cout << "\u001b[32m";
			std::cout << "Login successful" << std::endl;
			portal();
		}
	}
	// If login fails restart
	if (!isLoggedIn) {
		std::cout << "\x1B[2J\x1B[";
		std::cout << "\u001b[31m";
		std::cout << "Incorrect login information. Please try again" << std::endl;
		loginInfo();
	}
}

void User::portal() {
	int in;

	std::cout << "\u001b[36m";
	// Portal prompt
	std::cout << "______________________________\n";
	std::cout << "|        Library Portal      |\n";
	std::cout << "|                            |\n";
	std::cout << "|        1. Study Room       |\n";
	std::cout << "|   2. Chromebooks Checkout  |\n";
	std::cout << "|    3. Chromebooks Checkin  |\n";
	std::cout << "|                            |\n";
	std::cout << "------------------------------\n";

	std::cin >> in;

	// Switch statement
	switch (in) {
	case 1:
		std::cout << "\x1B[2J\x1B[";
		studyRooms();
		break;
	case 2:
		std::cout << "\x1B[2J\x1B[";
		chromebookCheckout();
		break;
	case 3:
		std::cout << "\x1B[2J\x1B[";
		chromebookCheckin();
		break;
	default:
		std::cout << "\x1B[2J\x1B[";
		welcome();
	}
}

void User::chromebookCheckout() {
	std::cout << "\u001b[31m";

	// Reading Json file
	std::ifstream o(R"(D:\Programing\BookingMadeBetter\data\chromebooks.json)");
	json data = json::parse(o);

	// Checks if chromebook is already checked out by person
	for (auto& i : data) {
		if (i["whoHas"] == id) {
			std::cout << "\x1B[2J\x1B[";
			std::cout << "\u001b[31m";
			std::cout << "You already have a chromebook checked out. " << std::endl;
			portal();
		}
	}

	// Checking which chromebooks are available
	std::cout << "Here are the chromebooks that are available:  " << std::endl;
	for (auto& i : data) {
		if (i["isAvailable"] == true) {
			std::cout << "Chromebook #" << i["serial"] << " is available."
				<< std::endl;
		}
	}

	// Asking user to select a chromebook to checkout
	std::cout << "Please select a chromebook to checkout: ";
	std::cin >> in;

	// Validating the request
	if (!data[in - 1]["isAvailable"]) {
		std::cout << "\u001b[31m";
		std::cout << "\x1B[2J\x1B[";
		std::cout << "That chrome is not available. Please select a different "
			"chromebook.";
		chromebookCheckout();
	}

	std::cout << "Please provide a reason for checkout.";
	std::cin >> inStr;

	// Adding to data
	data[in - 1]["isAvailable"] = false;
	data[in - 1]["whoHas"] = id;
	data[in - 1]["reason"] = inStr;



	// Writing to json file
	std::ofstream w("D:\\Programing\\BookingMadeBetter\\data\\chromebooks.json");
	w << std::setw(4) << data << std::endl;
	w.flush();

	std::cout << "\u001b[32m";
	std::cout << "\x1B[2J\x1B[";
	std::cout << "Successfully checked out chromebook #" << data[in - 1]["serial"]
		<< std::endl;

	portal();
}

void User::chromebookCheckin() {

	std::cout << "\u001b[33m";
	// Reading Json file
	std::ifstream o(R"(D:\Programing\BookingMadeBetter\data\chromebooks.json)");
	json data = json::parse(o);

	has = false;
	for (auto& i : data) {
		if (i["whoHas"] == id)
			has = true;
	}
	if (!has) {
		std::cout << "\u001b[31m";
		std::cout << "\x1B[2J\x1B[";
		std::cout << "You do not have any chromebooks checked out." << std::endl;
		portal();
	}

	std::cout << "Please enter the serial number of the chromebook you would "
		"like to return: ";
	std::cin >> in;

	if (data[in - 1]["whoHas"] != id) {
		std::cout << "\x1B[2J\x1B[";
		std::cout << "\u001b[31m";
		std::cout << "You do not have that chromebook checked out." << std::endl;
		chromebookCheckin();
	}

	// Adding to data
	data[in - 1]["isAvailable"] = true;
	data[in - 1]["whoHas"] = nullptr;
	data[in - 1]["reason"] = nullptr;


	// Writing to json file
	std::ofstream w(R"(D:\Programing\BookingMadeBetter\data\chromebooks.json)");
	w << std::setw(4) << data << std::endl;
	w.flush();

	std::cout << "\x1B[2J\x1B[";
	std::cout << "\u001b[32m";
	std::cout << "Thank you for returning your chromebook." << std::endl;
	portal();
}

void User::studyRooms() {
	std::cout << "\u001b[35m";

	// Reading Json file
	std::ifstream o(R"(D:\Programing\BookingMadeBetter\data\rooms.json)");
	json data = json::parse(o);

	std::cout << "Available Rooms: \n";
	std::cout << "1. Green Screen Rooms: \n";
	std::cout << "2. Adaptive Lab: \n";
	std::cout << "3. Study Room: \n";
	std::cout << "4. Meeting Room: \n";
	std::cout << "Please enter the room location: \n";

	std::cin >> in;

	// Getting input
	switch (in) {
	case 1:
		room = "Green Screen Room";
		break;
	case 2:
		room = "Adaptive Lab Room";
		break;
	case 3:
		room = "Study Room";
		break;
	case 4:
		room = "Meeting room";
		break;
	default:
		studyRooms();
	}

	std::cout << "Enter the time you want the room (08:00am to 03:00pm): ";
	std::cin >> time;

	// Converts time to 24 hour clock
	if (time[5] == 'a') {
		if (time[0] == '0') {
			timeStart = static_cast<int>(time[1]) - 48;
		}
		else {
			timeStart = +static_cast<int>(time[1]) - 48 + 10;
		}
	}

	if (time[5] == 'p') {
		if (time[0] == '0') {
			timeStart = static_cast<int>(time[1]) - 48 + 12;
		}
		else {
			timeStart = +static_cast<int>(time[1]) - 48 + 22;
		}
	}

	std::cout << "Enter how long you want the room for (Max 3 hours): ";
	std::cin >> max;

	if (max > 3 || max < 0) {
		std::cout << "\x1B[2J\x1B[";
		std::cout << "\u001b[31m";
		std::cout << "Invalid time please start over";
		studyRooms();
	}
	timeEnd = timeStart + max;

	// Checking if person already has one booking
	for (auto& i : data) {
		if (i["bookedBy"] == id) {
			std::cout << "\u001b[31m";
			std::cout << "\x1B[2J\x1B[";
			std::cout << "You already have a booking." << std::endl;
			portal();
		}
	}

	// Checking if already booked
	bool isValid = true;
	for (auto& i : data) {

		//this if statement checks what the room type is
		if (i["roomType"] == room) {

			//Big brain stuff --> we check to see if the time entered by the user does not interfere with other bookings
			//The first check is to see if the start time is greater than all of the start times
			if (timeStart > static_cast<double>(i["timeStart"]) &&

				//the next check is to see if the start time is less then the end time of all the bookings
				//those two conditions ensure that the booking attempt does not overlap with previous bookings
				timeStart < static_cast<double>(i["timeEnd"]) ||
				// this condition is to check if the end time is greater than any of the start times of existing bookings
				timeEnd > static_cast<double>(i["timeStart"]) &&
				//this condition is to see if the end time is less than any of the end times of existing bookings
				//these two checks ensure that the end time does not interfere with any existing bookings
				timeEnd < static_cast<double>(i["timeEnd"])) {
				//if either of those two conditions are true, the booking will not work and will output an error message because the booking time interferes with an existing booking
				isValid = false;

				// this if statement checks to see if the booking time is before or after working hours
				if (timeStart < 8 || timeEnd > 15) {
					std::cout << "Error 2" << std::endl;
					isValid = false;
					break;
				}
			}
		}
		// If it is a valid time and date it saves it to the json
		if (isValid) {
			in = data.size();
			data[in]["roomType"] = room;
			data[in]["timeStart"] = timeStart;
			data[in]["timeEnd"] = timeEnd;
			data[in]["max"] = max;
			data[in]["bookedBy"] = id;

			// Writing to json file
			std::ofstream w(R"(D:\Programing\BookingMadeBetter\data\rooms.json)");
			w << std::setw(4) << data << std::endl;
			w.flush();
			std::cout << "\u001b[32m";
			std::cout << "\x1B[2J\x1B[";
			std::cout << "\nMinimum 2 people per room.\n No food or drinks allowed. " << std::endl;
			portal();
		}
		std::cout << "\u001b[31m";
		std::cout << "\x1B[2J\x1B[";
		std::cout << "Invalid Time." << std::endl;
		studyRooms();
	}
}