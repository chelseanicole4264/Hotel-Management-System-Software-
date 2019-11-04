/*
Purpose: Customer Class for Hotel System 
-- This class will include account information, reservation, and reward system all for the customer 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Reservartions.h"

using namespace std;

class userCustomer {
private:
	int cUsernameSize;
	int cPasswordSize;
	// Customer Account Datatypes 
	int customerID = 0; /* Retrieve from db*/
	int rewards = 0; 
	string firstName = " ";
	string lastName = " "; 
	string userName = " ";
	string phoneNumber = " ";
	string emailAddress = " ";
	string password = " ";
	//Customer Reservation Datatypes
	reservationClass r; 
	string customerFirstName, customerLastName, duration;
	string month, day, year, monthOut, dayOut, yearOut;
	int package, guest;
	string  y = "yes";
	string n = "no";
	ofstream bookingCustomer;
	string customerCheckIn = " / / /", customerCheckOut = " / / /";
	HotelDB  hotel; 

	// Customer Reward Points Datatypes


public: 
/* CUSTOMER ACCOUNT */

// Customer Account Information Function
	void customerCreateAccount() {

	//Customer Enters Account Information 
		cout << "To create your account, please enter the following details below: " << endl; 
		cout << "Name: ";
		cin >> firstName >> lastName;
		cout << "Email: ";
		cin >> emailAddress;
		cout << "Phone Number: ";
		cin >> phoneNumber;
		cout << "Username (Must be at least 8 characters) : ";
		cin >> userName;
		cout << endl;
	// Checking the size of the username 
		cUsernameSize = userName.length();
		while (cUsernameSize > 8 || cUsernameSize < 8) {
			cout << "Please make sure your username is at least 8 characters long" << endl; 
			cout << "Username: " << endl;
			cin >> userName;
			cUsernameSize = userName.length();
		}
		cout << "Password (Must be at least 6 characters): "; 
		cin >> password;
		cout << endl; 
		cPasswordSize = password.length();
		while (cPasswordSize > 6 || cPasswordSize < 6){
			cout << "Please make sure your password is at least 6 characters long!! ";
			cout << "Password: ";
			cin >> password;
		}

	// Save Customer Account Info 
		hotel.saveCustomerData(userName, password, firstName, lastName, emailAddress, phoneNumber);
		
		if (hotel.customerExists())
		{
			cout << "You're Account Information has been saved! " << endl;
			cout << "To Proceed, Please Login! " << endl;
		}
		else 
		{	
			cout << "Account information could not be saved! Please try again! " << endl;
		}

		customerLogin(); 
	}
// Customer Menu Option for Login
	void customerMenuOptionTwo() {
		int customerChoice;
		cout << endl;
		cout << "******************************************" << endl;
		cout << "        MO's Hotel Customer Account " << endl;
		cout << "******************************************" << endl;
		cout << "       1. Account Information" << endl;
		cout << "       2. Reservation" << endl;
		cout << "       3. Reward Points " << endl;
		cout << "       4. Hotel Amentities" << endl;
		cout << "	    Press X to exit! " << endl;
		cout << "       Please Make a Choice: ";
		cin >> customerChoice;
		switch (customerChoice) {
		case 1:
			customerAccountInformation();
			break;
		case 2:
			customerReservation();
			break;
		case 3:
			customerRewardPoints();
			break;
		case 4:
			customerHotelAmentities();
			break;
		default:
			cout << endl;
			cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			cout << "GOODBYE :)" << endl;
			break;
		}
	}

// Customer Login to System 
	void customerLogin() {
		string line;

		cout << endl;
		cout << " Welcome to Mo's Hotel " << endl;
		cout << "Username: " << endl;
		cin >> userName;
		cout << endl;
		cUsernameSize = userName.length();
		while (cUsernameSize > 8 || cUsernameSize < 8) {
			cout << "Remember your username has to be 8 characters long. Please try again!" << endl;
			cin >> userName;
			cUsernameSize = userName.length();
		}
		cout << "Password: " << endl;
		cin >> password;
		cout << endl;
		cPasswordSize = password.length();
		while (cPasswordSize > 6 || cPasswordSize < 6) {
			cout << "Remember your username has to be 8 characters long. Please try again!" << endl;
			cin >> password;
			cPasswordSize = password.length();
		}

		hotel.getCustomerData(customerID, userName, password, firstName, lastName, emailAddress, phoneNumber, rewards);
		customerMenuOptionTwo();
	}
// Customer Account File Information

	void customerAccountInformation() {
		string y = "yes";
		cout << endl << "     Customer Account Details" << endl;
		cout << " Name: " << firstName <<" "<< lastName << endl;
		cout << " Email: " << emailAddress << endl;
		cout << " Phone Number: " << phoneNumber << endl;
		cout << " Username: " << userName << endl;
		cout << " Password: " << password << endl;

		cout << "Would you like to go back to the home screen? ";
		if (cin >> y) {
			customerMenuOptionTwo();
		}
		else {
			cout << "Thank you for choicing Mo's Hotel we look forward to serving you in the future! " << endl;
		}
	}

/* RESERVATIONS FOR CUSTOMER*/

// Customer Reservation Menu Fucntion 
	void customerReservation() {
		string y = "yes";
		string n = "no";
		int choice;
		cout << endl;
		cout << "******** Reservations ********" << endl;
		cout << "1. Book New Reservation " << endl;
		cout << "2. Cancel Current Reservation " << endl;
		cout << "Please Make a Choice: ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
			customerBookReservations();
		case 2:
			cancelCustomerReservation();
			break;
		default:
			break;
		}
	}
// Customer Reservations Bookings 
	void customerBookReservations() {
		string m = month, d = day, y = year;
		string m1 = month, d1 = day, y1 = year;

		cout << "To begin a new reservations booking, please enter the following details below: " << endl;
		cout << "First Name: ";
		cin >> customerFirstName;
		cout << "Last Name: ";
		cin >> customerLastName;
		cout << "# of Guest: ";
		cin >> guest; 
		customerCheckIn = r.checkInDate(m, d, y); // NOTE 
		customerCheckOut = r.checkOutDate(m1, d1, y1); // NOTE

		cout << "Packages, Would you like a special type? ";
		if (cin >> y) {
			cout << endl;
			customerRoomPackages();
		}
		else {
			cout << "The Following Rooms are below: " << endl;
			// NOTE what is suppose to happen here?
		}
	}

// Customer Add On Options
	void customerReservationAddOns() {

	}

	// Customer Room Packages Function
	void customerRoomPackages() {
		string y = "yes";
		string n = "no";
		int amentityOption, daysForAmen;
		int total = 0;

		vector<map<string, string>> allPackageInfo = hotel.getPackageTypes();

		// Room Packages Information 
		cout << endl;
		cout << "The Following Room Packages are listed below: " << endl;
		cout << endl;

		for (int i = 0; i < allPackageInfo.size(); i++)
		{
			cout << i + 1 << ". " << allPackageInfo[i]["PackageName"] << endl;
			cout << "Includes " << allPackageInfo[i]["PackageDescription"] << endl;
			if (allPackageInfo[i]["Amentities"] != "") {
				cout << "Hotel Amentities Included: " << allPackageInfo[i]["Amentities"] << endl;
			}
			cout << "Price: $" << allPackageInfo[i]["BaseCost"] << " a night" << endl << endl;
		}

		cout << "Which Package Would you like? ";
		cin >> package;

		while (package == 0 || package > allPackageInfo.size())
		{
			cout << "Please select from the packages listed above." << endl;
			cin >> package;
		}

		map<string, string> chosenPackage = allPackageInfo[package - 1];

		cout << "You've selected the " << chosenPackage["PackageName"] << ", excellent choice! " << endl;
		cout << endl;
		cout << "Would you like you to add on any amentities? " << endl << endl;

		if (cin >> y) {
			cout << "**** Hotel Amentities Add Ons ****" << endl;
			vector<map<string, string>> allAddonInfo = hotel.getAddons();

			for (int i = 0; i < allAddonInfo.size(); i++){
				cout << i + 1 << ". " << allAddonInfo[i]["AmenityName"] << " $" << allAddonInfo[i]["BaseCost"] << " a day," << allAddonInfo[i]["AmenityDescription"] << endl;
			}

			cout << "Which amentities would you like to add? " << endl;
			cin >> amentityOption;

			while (amentityOption == 0 || amentityOption > allAddonInfo.size())
			{
				cout << "Please select from the amentities listed above." << endl;
				cin >> amentityOption;
			}

			map<string, string> chosenAddon = allAddonInfo[amentityOption - 1];

			cout << endl;
			cout << "**** " << chosenAddon["AmenityName"] << " *****" << endl;
			cout << "How many days would you like to use the " << chosenAddon["AmenityName"] << " during your stay? ";
			cin >> daysForAmen;
			cout << "$" << stoi(chosenAddon["BaseCost"]) * daysForAmen << " added to your bill" << endl;
			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;

			total = stoi(chosenPackage["BaseCost"]) + (stoi(chosenAddon["BaseCost"]) * daysForAmen);
			cout << "Payment Total: $" << total << endl;
			r.getPayment();
			cout << endl;

			// NOTE Save Package NOTE Save reservation
			hotel.saveReservation(customerID, guest, customerCheckIn, customerCheckOut, chosenPackage["PackageTypeID"], chosenAddon["AddOnID"], daysForAmen, total);

			cout << "Would you like to go back to home menu? ";
			if (cin >> y) {
				customerMenuOptionTwo();
			}
			else if (cin >> n) {
				cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			}
		}
		else if (cin >> n) {
			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;
			r.getPayment();
			cout << endl;
			cout << "Would you like to go back to home menu? ";
			if (cin >> y) {
				customerMenuOptionTwo();
			}
			else if (cin >> n) {
				cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			}
		}
	}

	// Cancel Booking Reservations
	void cancelCustomerReservation() {
		string y = "yes";
		int selectedRes = 0;
		ifstream bookingCustomer;

		// Get all reservations for a customer and display them
		vector<map<string, string>> allReservationInfo = hotel.getReservations(customerID);

		// Room Packages Information 
		cout << endl;
		cout << "The Following Room Packages are listed below: " << endl;
		cout << endl;

		for (int i = 0; i < allReservationInfo.size(); i++)
		{
			cout << i + 1 << ". Customer Reservation Details      " << endl;
			cout << "	Name: " << allReservationInfo[i]["FirstName"] << " " << allReservationInfo[i]["LastName"] << endl;
			cout << "	# of Guest During Stay : " << allReservationInfo[i]["NumberOfGuests"] << endl;
			cout << "	Duration of Stay: " << allReservationInfo[i]["CheckInDate"] << " TO " << allReservationInfo[i]["CheckOutDate"] << endl;
			cout << "	Package: " << allReservationInfo[i]["PackageTypeID"] << endl;
			cout << "	" << allReservationInfo[i]["PackageName"] << endl;
			cout << "	Price: $" << allReservationInfo[i]["BaseCost"] << " a night" << endl;

			if (allReservationInfo[i]["AmenityName"] != "") {
				cout << "	Added Amenities: " << allReservationInfo[i]["AmenityName"] << " for " << allReservationInfo[i]["AddOnDays"] << " days" << endl;
			}

			cout << "	Total Cost: " << allReservationInfo[i]["TotalCost"] << endl << endl;
		}

		cout << "Please select the reservation you would like to cancel." << endl;
		cin >> selectedRes;

		while (selectedRes == 0 || package > allReservationInfo.size())
		{
			cout << "Please select a reservation listed above." << endl;
			cin >> selectedRes;
		}

		cout << "Would you like to cancel your reservation? ";
		if (cin >> y) 
		{
			map<string, string> chosenReservation = allReservationInfo[selectedRes-1];
			hotel.cancelReservation(customerID, stoi(chosenReservation["ReservationID"]));
			cout << "Your reservation has been canceled. If you would like to create a new reservation, please go back to the home screen! " << endl;
			chosenReservation.clear();
			customerMenuOptionTwo();
		}
	}

	// Customer Looks at reward points 
	void customerRewardPoints() {
		int p1Price = 195, p2Price = 155, p3Price = 250;
		int a1price = 10, a2price = 20, a3price = 30, a4price = 40, a5price = 60;
		ifstream bookingCustomer;
		bookingCustomer.open("CustomerReservationBookings.txt");
		if (bookingCustomer.is_open()) {
			cout << "            Customer Reservation Details      " << endl;
			cout << " Name: " << customerFirstName << customerLastName << endl;
			cout << " # of Guest During Stay : " << guest << endl;
			cout << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
			cout << " Package: " << package << endl;
			if (package == 1) {
				cout << " Single King Suite " << endl;
				cout << " Price: $195 a night " << endl;
				cout << " Hotel Amentities added: Hot Tub for 3 night " << endl;
				int total = p1Price + a1price;
				cout << " Total Price: $" << total << endl;
			}
			bookingCustomer.close();
		}
		cout << "The Reward Points are based on the price of the room. If you stay over 2 nights you get double the reward points for 2 nights. " << endl;
		cout << "Reward Points amount = 195 " << endl;
		cout << "It'll be added to your account! " << endl;


	}

	// Customer see hotel amentities
	void customerHotelAmentities() {
		int selectedChoice;
		string y = "yes";
		string n = "no";

		// Get all reservations for a customer and display them
		vector<map<string, string>> allAmenities = hotel.getHotelAmenities();

		cout << endl << "***** Mo's Hotels Amentities *****" << endl;
		cout << "With your stay you have the option to enjoy the following amentities below: " << endl;

		for (int i = 0; i < allAmenities.size(); i++)
		{
			cout << i + 1 << ". " << allAmenities[i]["AmenityName"] << endl;
		}
		
		cout << " If you want more information on each option, please select an option above ";
		cin >> selectedChoice;

		while (selectedChoice == 0 || selectedChoice > allAmenities.size())
		{
			cout << " If you want more information on each option, please select an option above ";
			cin >> selectedChoice;
		}

		map<string, string> selectedAmenity = allAmenities[selectedChoice - 1];

		cout << endl << "******** " << selectedAmenity["AmenityName"] << " ********" << endl;
		cout << selectedAmenity["AmenityDescription"] << endl;
		cout << selectedAmenity["Auxiliary1"] << endl;
		cout << selectedAmenity["Auxiliary2"] << endl;
		cout << selectedAmenity["Auxiliary3"] << endl;
		cout << selectedAmenity["Auxiliary4"] << endl;
		cout << selectedAmenity["Auxiliary5"] << endl;

		cout << "Thank you!!!!" << endl;
		cout << endl;
		cout << "Would you like to go back to home menu? ";
		if (cin >> y) {
			customerMenuOptionTwo();
		}
		else if (cin >> n) {
			cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
		}
	}
};