/*
Purpose: Employee Class for Hotel System
*/

#pragma once
#ifndef EMPLOYEECLASS_H
#define EMPLOYEECLASS_H

#include<iostream>
#include <string>
#include <fstream>
#include "Database.h"

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
	void getEmployeeData(string& userID, string& password, string& firstName, string& lastName)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;
			//hasEmployeeData = false;
			MYSQL* conn;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn, "localhost", "root", "MySQLPassword1", "HotelSystemDB", 3306, NULL, 0); // use your localhost password

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> eInfo = {
				{"EmployeeID"   , ""},
				{"FirstName"	, ""},
				{"LastName"		, ""},
				{"UserID"	    , ""},
				{"Password"	    , ""},
			};

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetEmployeeData('" + userID + "', '" + password + "')";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						for (int i = 0; i < numOfFields; i++)
						{
							eInfo[fields[i].name] = row[i];
						}
					}

					firstName = eInfo["FirstName"];
					lastName = eInfo["LastName"];
					userID = eInfo["UserID"];
					password = eInfo["Password"];

					//hasEmployeeData = true;
					eInfo.clear();
				}
				else
				{
					cout << "Unable to retrieve your account information." << endl;
				}
			}
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	void saveEmployeeData(string userID, string password, string firstName, string lastName)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			int qstate;
			MYSQL* conn;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn, "localhost", "root", "MySQLPassword1", "HotelSystemDB", 3306, NULL, 0); // use your localhost password


			if (conn)
			{
				string query = "CALL SaveEmployeeData('" + firstName + "', '" + lastName + "', '" + userID + "', '" + password + "')";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);
					//employeeSaved = true;
				}
				else
				{
					cout << "Unable to create your account." << endl;
				}
			}
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
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
			break;
		case 3:
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
	// Employee Account File 

		saveEmployeeData(eUserID, ePassword, eFirstName, eLastName);

		if (hotel.employeeExists())
		{
			cout << "Your Account Information has been saved! " << endl;
			cout << "To proceed, please LOGIN! " << endl;
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
		employeeMenu();
	}
// Employee Account Information: Menu Option #1
	void employeeAccountInformation() {
		string y = "yes";
		ifstream eAccountFile;
		eAccountFile.open("EmployeeAccount.txt");
		if (eAccountFile.is_open()) {
			cout << "        Employee Account Details" << endl;
			cout << " Name: " << eFirstName << eLastName << endl;
			cout << "User ID: " << eUserID << endl;
			cout << "Password: " << ePassword << endl;
			eAccountFile.close();
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
// Employee Customer Check IN 
	void employeeCheckIn() {

	}
};
#endif

