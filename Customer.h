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
	int customerID = 0;
	int rewards = 0; 
	string firstName = " ";
	string lastName = " "; 
	string userName = " ";
	string phoneNumber = " ";
	string emailAddress = " ";
	string password = " ";
	//Customer Reservation Datatypes 
	string customerFirstName, customerLastName, duration;
	string month, day, year, monthOut, dayOut, yearOut;
	int package, guest;
	string  y = "yes";
	string n = "no";
	string customerCheckIn = " / / /", customerCheckOut = " / / /";
	HotelDB  hotel; 
	reservationClass res;
	
	int calculateRewards(int total)
	{
		int adjustedRewards = rewards;
		return adjustedRewards += total;
	}

	bool customerDataLoaded = false;
	bool customerSaved = false;

	#pragma region Database Calls
	void getCustomerData()
	{
		string query = "CALL GetCustomerData('" + userName + "', '" + password + "')";
		map <string, string> cInfo = hotel.getCustomerData(query);

		// Set the data
		if (!cInfo.empty()) {
			customerID = stoi(cInfo["CustomerID"]);
			firstName = cInfo["FirstName"];
			lastName = cInfo["LastName"];
			userName = cInfo["UserName"];
			password = cInfo["Password"];
			phoneNumber = cInfo["PhoneNumber"];
			emailAddress = cInfo["EmailAddress"];
			rewards = stoi(cInfo["RewardsPoints"]);
			customerDataLoaded = true;
			cInfo.clear();
		}
		else
		{
			customerDataLoaded = false;
		}
	}

	void saveCustomerData(string cUserName, string cPassword, string cFirstName, string cLastName, string cEmailAddress, string cPhoneNumber)
	{
		string query = "CALL SaveCustomerData('" + cFirstName + "', '" + cLastName + "', '" + cUserName + "', '" + cPassword + "', '" + cPhoneNumber + "', '" + cEmailAddress + "')";
		customerSaved = hotel.saveToDatabase(query);		
	}

	#pragma endregion


public: 
/* CUSTOMER ACCOUNT */

	int menuOptionCheck(int selectedItem, int menuSize, string message)
	{
		cout << message << endl;
		cin >> selectedItem;

		while (selectedItem == 0 || selectedItem > menuSize)
		{
			if (selectedItem == 0) {
				customerMenuOptionTwo();
			}

			cout << message << endl;
			cin >> selectedItem;
		}

		return selectedItem;
	}

// Customer Account Information Function
	void customerCreateAccount() 
	{
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
		while (cPasswordSize > 6 || cPasswordSize < 6) {
			cout << "Please make sure your password is at least 6 characters long!! ";
			cout << "Password: ";
			cin >> password;
		}

		// Save Customer Account Info 
		saveCustomerData(userName, password, firstName, lastName, emailAddress, phoneNumber);

		if (customerSaved)
		{
			cout << "You're Account Information has been saved! " << endl;
			cout << "To Proceed, Please Login! " << endl;
		}
		else
		{
			cout << "Account information could not be saved! Please try again! " << endl;
			customerMenuOptionTwo();
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

		getCustomerData();

		if (customerDataLoaded) 
		{
			customerMenuOptionTwo();
		}
		else
		{
			cout << "Unable to retrieve account information. Please try again!" << endl;
			customerLogin();
		}
		
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
		customerCheckIn = res.checkInDate(m, d, y); // NOTE 
		customerCheckOut = res.checkOutDate(m1, d1, y1); // NOTE

		cout << "Packages: ";//, Would you like a special type? ";
//		if (cin >> y) {
			cout << endl;
			customerRoomPackages(); // NOTE: Add fields if they are avaiable or not
	//	}
		
	}

	// Customer Room Packages Function
	void customerRoomPackages() {
		string y = "yes";
		string n = "no";
		int amentityOption = 0;
		int daysForAmen = 0;
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
		package = menuOptionCheck(package, allPackageInfo.size(), "Please select from the packages listed above.");

		map<string, string> selectedPackage = allPackageInfo[package - 1];
		map<string, string> selectedAddon;
		
		cout << "You've selected the " << selectedPackage["PackageName"] << ", excellent choice! " << endl;
		cout << endl;
		cout << "Would you like you to add on any amentities? " << endl << endl;

		if (cin >> y) {
			cout << "**** Hotel Amentities Add Ons ****" << endl;
			vector<map<string, string>> allAddonInfo = hotel.getAddons();

			// Display all available addons
			for (int i = 0; i < allAddonInfo.size(); i++){
				cout << i + 1 << ". " << allAddonInfo[i]["AmenityName"] << " $" << allAddonInfo[i]["BaseCost"] << " a day," << allAddonInfo[i]["AmenityDescription"] << endl;
			}

			cout << "Which amentities would you like to add? " << endl;
			amentityOption = menuOptionCheck(amentityOption, allAddonInfo.size(), "Please select from the amentities listed above.");

			selectedAddon = allAddonInfo[amentityOption - 1];

			cout << endl;
			cout << "**** " << selectedAddon["AmenityName"] << " *****" << endl;
			cout << "How many days would you like to use the " << selectedAddon["AmenityName"] << " during your stay? ";
			cin >> daysForAmen;
			cout << "$" << stoi(selectedAddon["BaseCost"]) * daysForAmen << " added to your bill" << endl;
			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;

			total = stoi(selectedPackage["BaseCost"]) + (stoi(selectedAddon["BaseCost"]) * daysForAmen);
			cout << "Payment Total: $" << total << endl;
			res.getPayment();
			cout << endl;

			// Save reservation
			res.saveReservation(customerID, guest, customerCheckIn, customerCheckOut, selectedPackage["PackageTypeID"], selectedAddon["AddOnID"], daysForAmen, total, calculateRewards(total), 0, 0);

			cout << "Would you like to go back to home menu? ";
			if (cin >> y) {
				customerMenuOptionTwo();
			}
			else if (cin >> n) {
				cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			}
		}
		else if (cin >> n) {
			
			// Save reservation
			res.saveReservation(customerID, guest, customerCheckIn, customerCheckOut, selectedPackage["PackageTypeID"], selectedAddon["AddOnID"], daysForAmen, total, calculateRewards(total), 0, 0);

			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;
			res.getPayment();
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
	void cancelCustomerReservation() 
	{
		res.cancelCustomerReservation(customerID);

		if (res.reservationCancelled)
		{
			cout << "Your reservation has been cancelled. If you would like to create a new reservation, please go back to the home screen! " << endl;
			customerMenuOptionTwo();
		}
		else
		{
			cout << "Your reservation was NOT cancelled." << endl;
			customerMenuOptionTwo();
		}
	}

	// Customer Looks at reward points 
	void customerRewardPoints() {

		int selectedMenuItem = 0;
		vector<map<string, string>> eligibleRewards;
		map<string, string> selectedReward;
		int currentRewards, requiredRewards, adjustedRewards, reward = 0;
		string query = "";

		if (!customerDataLoaded)
		{
			cout << "Unable to retrieve Rewards. Please try again later..." << endl;
			customerMenuOptionTwo();
		}

		// Display customer name and rewards
		cout << endl << endl << "            Customer Rewards Details      " << endl;
		cout << "Name: " << firstName << " " << lastName << endl;
		cout << "Current Rewards Total: " << rewards << endl << endl;

		cout << "Please select an option below or select '0' to return to the main menu:" << endl;
		cout << " 1. Redeem Rewards" << endl;
		cout << " 2. View Rewards History" << endl;
		cout << " 3. How Rewards Work" << endl;

		selectedMenuItem = menuOptionCheck(selectedMenuItem, 3, "Please select an option below or select '0' to return to the main menu:");

		switch (selectedMenuItem)
		{
		case 1:
			// Redeem Rewards

			// Get Eligible Rewards
			eligibleRewards = hotel.getEligibleRewards(customerID);

			if (eligibleRewards.size() == 0) {
				cout << "Whoops! Looks like you are not eliglble for rewards at this time. Please make a reservation to gather more points!" << endl << endl;
				customerMenuOptionTwo();
			}

			// Display Eligible Rewards
			cout << "Please Select the reward you would like to redeem." << endl << endl;
			for (int i = 0; i < eligibleRewards.size(); i++)
			{
				cout << i + 1 << ". Reward : " << eligibleRewards[i]["RewardName"] << endl;
				cout << "   Details : " << eligibleRewards[i]["RewardDescription"] << endl;
				cout << "   Cost : " << eligibleRewards[i]["RequiredRewards"] << "pts" << endl << endl;
			}

			// Get the selected Reward
			reward = menuOptionCheck(reward, eligibleRewards.size(), "Please Select the reward you would like to redeem.");
			selectedReward = eligibleRewards[reward - 1];

			// Adjust Rewards Points
			currentRewards = rewards;
			requiredRewards = stoi(selectedReward["RequiredRewards"]);
			adjustedRewards = currentRewards - requiredRewards;

			// Update customers total rewards
			query = "CALL UpdateRewards(" + to_string(customerID) + "," + to_string(adjustedRewards) + ")";
			hotel.saveToDatabase(query);

			// Apply reward to Reservation and adjust pricing(if any)
			//cout << "Reward Points amount = 195 " << endl;
			//cout << "It'll be added to your account! " << endl;

			// Add Rewards Transaction to the Rewards log

			customerMenuOptionTwo();
		case 2:
			// View Rewards History (would have to create separate table to house all the rewards transactions)
			customerMenuOptionTwo();
		case 3:
			// How Rewards Work
			cout << "The Reward Points are based on the price of the room. They price of a reservation will be the amount of points a customer is awarded when they make a reservation." << endl;
			cout << "Points are awarded each time a customer schedules a reservation." << endl << endl;
			customerMenuOptionTwo();
		default:
			customerMenuOptionTwo();
		}
	}

	// Customer see hotel amentities
	void customerHotelAmentities() {
		int selectedChoice = 0;
		string y = "yes";
		string n = "no";

		// Get all reservations for a customer and display them
		vector<map<string, string>> allAmenities = hotel.getHotelAmenities();
		map<string, string> selectedAmenity;

		cout << endl << "***** Mo's Hotels Amentities *****" << endl;
		cout << "With your stay you have the option to enjoy the following amentities below: " << endl;

		for (int i = 0; i < allAmenities.size(); i++)
		{
			cout << i + 1 << ". " << allAmenities[i]["AmenityName"] << endl;
		}
		

		selectedChoice = menuOptionCheck(selectedChoice, allAmenities.size(), " If you want more information on each option, please select an option above ");
		selectedAmenity = allAmenities[selectedChoice - 1];

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