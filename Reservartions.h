/*
Purpose: Employee Class for Hotel System
*/

#pragma once
#include <iostream>
#include <string>
using namespace std;

class reservationClass {
private:
	string month, day, year, monthOut, dayOut, yearOut;
	string firstNameRewards, lastNameRewards, nameRewards;
	string checkOutMonth, checkOutday, checkOutYear;
	HotelDB hotel;
	MenuHelper mh;

public: 
	bool foundRes = false;
	bool reservationSaved = false;
	bool reservationCancelled = false;

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

	#pragma region Database Calls
	void saveReservation(int customerID, int numGuests, string checkInDate, string checkOutDate, string packageTypeID, string addonID, int addonDays, int totalCost, int adjustedRewards,
		int available, int underMaintenance)
	{
		hotel.setQuery("CALL SaveReservation(" + to_string(customerID) + ", " + to_string(numGuests) + ", '" + checkInDate + "', '" + checkOutDate
			+ "', " + packageTypeID + " ," + addonID + ", " + to_string(addonDays) + ", " + to_string(totalCost) + ", " + to_string(adjustedRewards)
			+ " ," + to_string(available) + ", " + to_string(underMaintenance) + ")");

		reservationSaved = hotel.saveToDatabase();
	}


	void cancelReservation(int customerID, int reservationID)
	{
		hotel.setQuery("CALL CancelReservation(" + to_string(customerID) + ", " + to_string(reservationID) + ")");
		reservationCancelled = hotel.saveToDatabase();
	}

	#pragma endregion

	void cancelCustomerReservation(int customerID) {
		string y = "yes";
		int selectedRes = 0;

		// Get all reservations for a customer and display them
		vector<map<string, string>> allReservationInfo = hotel.getReservations(customerID);

		// Display all reservations
		printReservationDetails(allReservationInfo);

		if (!foundRes)
		{
			reservationCancelled = false;
			return;
		}

		// Get the reservation to be cancelled
		selectedRes = mh.menuOptionCheck(allReservationInfo.size(), "Please select the reservation you would like to cancel or select '0' to return to the main menu:");

		if (selectedRes == 0) {
			reservationCancelled = false;
			return;
		}

		// Confirm cancellation
		cout << "Would you like to cancel your reservation? ";
		if (cin >> y)
		{
			map<string, string> selectedReservation = allReservationInfo[selectedRes - 1];
			cancelReservation(customerID, stoi(selectedReservation["ReservationID"]));
			selectedReservation.clear();
		}
		else
		{
			reservationCancelled = false;
		}
	}
	
	void printReservationDetails(vector<map<string, string>> allReservationInfo)
	{
		if (allReservationInfo.empty())
		{
			cout << "	No Reservations Found." << endl << endl;
			foundRes = false;
		}
		else { foundRes = true; }

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
	}
	
	//int menuOptionCheck(int selectedItem, int menuSize, string message)
	//{
	//	cout << message << endl;
	//	cin >> selectedItem;

	//	while (selectedItem == 0 || selectedItem > menuSize)
	//	{
	//		if (selectedItem == 0) {
	//			return 0; //NOTE
	//		}

	//		cout << message << endl;
	//		cin >> selectedItem;
	//	}

	//	return selectedItem;
	//}
};