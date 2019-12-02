/*
Purpose: Employee Class for Hotel System
*/

#pragma once
#ifndef EMPLOYEECLASS_H
#define EMPLOYEECLASS_H

#include<iostream>
#include <string>
#include <fstream>
#include "Reservartions.h"

using namespace std;
class employeeClass
{
private:
// Employee Account Details 
	string eFirstName = " ";
	string eLastName = " ";
	int e1ID, e2ID, e3ID;
	string eUserID; 
	string ePassword;
	int eUserIDSize;
	int ePasswordSize;
	HotelDB hotel;
	int currentCustomerID = 0;
	reservationClass res;

	#pragma region Database Calls
		bool employeeDataLoaded = false;
		bool employeeSaved = false;

		void getEmployeeData()
		{
			string query = "CALL GetEmployeeData('" + eUserID + "', '" + ePassword + "')";
			map <string, string> eInfo = hotel.getEmployeeData(query);

			if (!eInfo.empty()) {
				eFirstName = eInfo["FirstName"];
				eLastName = eInfo["LastName"];
				eUserID = eInfo["UserID"];
				ePassword = eInfo["Password"];
				employeeDataLoaded = true;
				eInfo.clear();
			}
			else
			{
				employeeDataLoaded = false;
			}
		}

		void saveEmployeeData(string userID, string password, string firstName, string lastName)
		{
			string query = "CALL SaveEmployeeData('" + firstName + "', '" + lastName + "', '" + userID + "', '" + password + "')";
			employeeSaved = hotel.saveToDatabase(query);
		}
	#pragma endregion

		void editReservation() {
			if (currentCustomerID != 0) {
				// Get all the resevations under that customer ID
				vector<map<string, string>> allReservationInfo = hotel.getReservations(currentCustomerID);
				res.printReservationDetails(allReservationInfo);
			}

			// Select a reservation to edit

			// Get the ReservationID
			string query = "";
			
			// Select what to edit
			//PackageType
			//Number of Guests
			//Check in dates
		}

		void cancelReservation() 
		{
			if (currentCustomerID != 0) {
				res.cancelCustomerReservation(currentCustomerID);
				
				if (res.reservationCancelled) 
				{
					cout << "Reservation for customer has been cancelled." << endl;
					employeeMenu();
				}
				else
				{
					cout << "Reservation for customer was NOT cancelled. Please try again later" << endl;
					employeeMenu();
				}
			}
		}

public:
// Employee Menu 
	void employeeMenu() {
		int choice; 

		// Menu Options 
		cout << "****** Mo's Hotels Employees ******" << endl; 
		cout << " 1. Employee Acount " << endl; 
		cout << " 2. Reservations " << endl; 
		cout << " 3. Hotel Summary Report " << endl; 
		cout << " 4. Exit Program " << endl; 
		cin >> choice; 

		switch (choice) {
		case 1:
			employeeAccountInformation();
			break;
		case 2:
			employeeReservationCheck();
			break;
		case 3:
			hotelSummaryReport();
			break;
		case 4:
			break;
		}
	}

// Employee Create Account 
	void employeeCreateAccount() {
	// Employee Enters Account Info 
		cout << " Welcome to Mo's Hotel! " << endl; 
		cout << "For all new employess, enter the following information below..." << endl;
		cout << "Name: ";
		cin >> eFirstName >> eLastName;
		cout << "Employee UserID # (Must be atleast 4 numbers) : "; 
		cin >> eUserID;
		cout << endl;
		// UserID Size Check 
		eUserIDSize = eUserID.length();
		while (eUserIDSize > 4 || eUserIDSize < 4) {
			cout << "Please make sure your user ID is atleast 4 characters long!!! " << endl; 
			cout << "UserID: ";
			cin >> eUserID;
			eUserIDSize = eUserID.length();
		}
		cout << "Employee Password (Must be atleast 6 characters): ";
		cin >> ePassword;
		cout << endl; 
		// Password Size Check 
		ePasswordSize = ePassword.length();
		while (ePasswordSize > 6 || ePasswordSize < 6) {
			cout << "Please make sure your password is aleats 6 characters long!!! ";
			cout << "Password: ";
			cin >> ePassword;
		}
	
		// Save Employee Account Info
		saveEmployeeData(eUserID, ePassword, eFirstName, eLastName);

		if (employeeSaved)
		{
			cout << "Your Account Information has been saved! " << endl;
			cout << "To proceed, please Login! " << endl;
		}
		else 
		{
			cout << "Account information countn't be saved, please try again! " << endl;
		}
		employeeLogin();
	}

// Employee Login 
	void employeeLogin() {
		cout << "******** Emplpyee Login ********" << endl; 
		cout << "Employee User ID: ";
		cin >> eUserID;
		eUserIDSize = eUserID.length();
		while (eUserIDSize > 4 || eUserIDSize < 4) {
			cout << "INCORRECT!  Remember your User ID has to be atleasr 4 characters long. Please try again! " << endl; 
			cin >> eUserID;
			eUserIDSize = eUserID.length();
		}
		cout << "Employee Password: ";
		cin >> ePassword;
		ePasswordSize = ePassword.length();
		while (ePasswordSize > 6 || ePasswordSize < 6) {
			cout << "INCORRECT! Remember your Password has to be atleast 6 characters long. Please try again! " << endl; 
			cin >> ePassword;
			ePasswordSize = ePassword.length();
		}

		getEmployeeData();
		if (employeeDataLoaded)
		{
			employeeMenu();
		}
		else {
			cout << "Unable to retrieve account information. Please try again!" << endl;
			employeeLogin();
		}
	}
// Employee Account Information: Menu Option #1
	void employeeAccountInformation() {
		string y = "yes";

		if (employeeDataLoaded) {
			cout << "        Employee Account Details" << endl;
			cout << " Name: " << eFirstName << eLastName << endl;
			cout << " User ID: " << eUserID << endl;
			cout << " Password: " << ePassword << endl;
		}
		cout << "Would you like to go back to the home screen? ";
		if (cin >> y) {
			employeeMenu();
		}
		else {
			cout << "Have a great day!" << endl;
		}
	}
/* EMPLOYEE CUSTOMER RESERVATION CHECK */
	void employeeReservationCheck() 
	{
		string cFirstName, cLastName, phoneNumber;

		// Enter Customer Information
		cout << "Please enter the first and last name of customer along with their phone number: " << endl;
		cout << "First Name : ";
		cin >> cFirstName;
		cout << "Last Name : ";
		cin >> cLastName;
		cout << "Phone Number : ";
		cin >> phoneNumber;
		cout << endl << endl;

		// Get a customers ID Number based on first name, last name and phone number
		string query = "SELECT CustomerID FROM Customer WHERE FirstName = '" + cFirstName + "'and LastName = '" + cLastName + "' and PhoneNumber = '" + phoneNumber + "';";
		map <string, string> cInfo = hotel.getCustomerData(query);
		// Set the data
		if (!cInfo.empty()) {
			int eChoice;
			currentCustomerID = stoi(cInfo["CustomerID"]);

			cout << "Customer Found!" << endl << endl;
			cout << "       1. Edit a reservation" << endl;
			cout << "       2. Cancel a reservation " << endl;
			cout << "       Please Make a Choice: ";
			cin >> eChoice;
			switch (eChoice) {
			case 1:
				editReservation();
				break;
			case 2:
				cancelReservation();
				break;
			default:
				break;
			}
		}
		else {
			cout << "A customer with that criteria does not exist. Please try again!" << endl;
			employeeReservationCheck();
		}
	}
/* EMPLOYEE HOTEL SUMMARY REPORT */
	void hotelSummaryReport() 
	{
		// call the stored procedure that has all the data
		vector<map<string, string>> summaryReport = hotel.getSummaryReport();

		// display it
		for (int i = 0; i < summaryReport.size(); i++)
		{
			cout << "Summary Report     " << endl;
			cout << "	Total Number of Reservations: " << summaryReport[i]["NumReservations"] << endl;
			cout << "	# of rooms currently available: " << summaryReport[i]["NumAvailableRooms"] << endl;
			cout << "	# of rooms under maintenance " << summaryReport[i]["NumUnderMaintenance"] << endl;
			
			//cout << "	Reservation Total: " << summaryReport[i]["TotalCost"] << endl << endl;
		}
	}
};
#endif

