/*
Purpose: Employee Class for Hotel System
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class reservationClass {
private:
	string month, day, year, monthOut, dayOut, yearOut;
	string firstNameRewards, lastNameRewards, nameRewards;
	string checkOutMonth, checkOutday, checkOutYear;

public: 
// Check In Function 
	string checkInDate(string m, string d, string y) {
	// Setting Date Variables 
		string checkInDate;
		month = m; 
		day = d;
		year = y;

		cout << "Please enter the date you wish to check in: " << endl;
		cout << "Month: ";
		cin >> m;
		cout << "Day: ";
		cin >> d;
		cout << "Year: "; 
		cin >> y; 
		cout << "Your Check In Date is as follows... " << m << " /"  << d << "/ " << y << endl; 

		checkInDate = m.append("/") + d.append("/") + y;

		return checkInDate; 
	}
// Check Out Function
	string checkOutDate(string m1, string d1, string y1) {
		string checkOutDate;
		month = m1;
		day = d1;
		year = y1;
		
		cout << "Please enter the date you wish to check out: " << endl;
		cout << "Month: ";
		cin >> m1;
		cout << "Day: ";
		cin >> d1;
		cout << "Year: ";
		cin >> y1;
		cout << "Your Check Out Date is as follows.... " << m1 << " /" << d1 << "/ " << y1 << endl;
		
		checkOutDate = m1.append("/") + d1.append("/") + y1;

		return checkOutDate;
	}
// Room Packages Function 
	void roomPackages() {
		int package; 
		cout << " ******Room Packages****** " << endl; 
		cout << endl; 
		cout << "1. Single King Suite " << endl;
		cout << "Includes: TV, Free Wifi, Window View, Mini Suite Kitchen" << endl; 
		cout << "Hotel Amentities Included: Pool, Breakfast, Fitness Center," << endl;
		cout << "Price: $195 a night" << endl; 

		cout << "2. Double King Suite " << endl;
		cout << "Includes: TV, Free Wifi, Window View, Mini Suite Kitchen" << endl;
		cout << "Hotel Amentities Included: Pool, Breakfast, Fitness Center ," << endl;
		cout << "Price: $195 a night" << endl;

		cout << "3. Deluxe Suite  " << endl; 
		cout << "Include: TV, Free Wifi, Window View, Jetted Tub, Full Kitchenate Area" << endl;
		cout << "Hotel Amentities Included: Pool, Breakfast, Fitness Center (Unlimited Use), Hot Tub (Unlimited Access)" << endl;
		cout << "Price: $300 a night" << endl; 

		cout << "4. Press any key to exit" << endl;
		cout << "Which Package would you like to add? " << endl; 
		cin >> package;
		switch (package) {
		case 1:
			cout << "You've selected the Single Suite, excellent choice! " << endl;
			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;
			getPayment();
			break;
		case 2:
			cout << "You've selected the Double Suite, excellent choice! " << endl;
			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			getPayment();
			cout << endl;
			break;
		case 3:
			cout << "You've selected the Delux Suite, the best choice! " << endl;
			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;
			getPayment();
			break;
		case 4:
			cout << "Thank you for choicing Mo's Hotels! " << endl;
			break;
		}
	}
// Payment Processing 
	void getPayment() {
		string cardName, cardNumber, cardType, cardTrans;
		string y = "yes";
		string n = "no";
		cout << "**** Payment Details ****" << endl;
		cout << "Enter the name on the card: ";
		cin >> cardName;
		cout << "Enter card type (Visa, Master, etc):  ";
		cin >> cardType;
		cout << "Debit or Credit? ";
		cin >> cardTrans;
		cout << "Enter the credit card number: ";
		cin >> cardNumber;
	}

};