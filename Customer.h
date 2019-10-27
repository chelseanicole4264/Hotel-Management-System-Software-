/*
Purpose: Customer Class for Hotel System 
-- This class will include account information, reservation, and reward system all for the customer 
*/

#include <iostream>
#include <string>
#include <fstream>
#include "Reservartions.h"
using namespace std;

class userCustomer {
private:
	int cUsernameSize;
	int cPasswordSize;
	// Customer Account Datatypes 
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
	// Customer Reward Points Datatypes
public: 
/* CUSTOMER ACCOUNT */

// Customer Account Information Function
	void customerCreateAccount() {
		ofstream accountFile;
		accountFile.open("CustomerAccount.txt");
	//Customer Enters Account Information 
		cout << "To create your account, please enter the following details below: " << endl; 
		cout << "Name: ";
		cin >> firstName >> lastName;
		cout << "Email: ";
		cin >> emailAddress;
		cout << "Phone Number: ";
		cin >> phoneNumber;
		cout << "Username (Must be at least 8  characters) : ";
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
	//Customer Account File Info 
		if (accountFile.is_open()) {
			accountFile << "     Customer Account Details" << endl;
			accountFile << " Name: " << firstName << lastName << endl;
			accountFile << " Email: " << emailAddress << endl;
			accountFile << " Phone Number: " << phoneNumber << endl;
			accountFile << " Username: " << userName << endl;
			accountFile << " Password: " << password << endl;
			accountFile.close();
			cout << "You're Account Information has be saved! " << endl;
			cout << "To Proceed, Please Login! " << endl;
			cout << endl;
		}
		else {
			cout << "Account information could not be saved! Please try again! " << endl; 
		}
		accountFile.close();
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
		ifstream accountFile;
		string line;
		accountFile.open("CustomerAccount.txt");
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
		customerMenuOptionTwo();
	}
// Customer Account File Information 
	void customerAccountInformation() {
		string y = "yes";
		ifstream accountFile;
		accountFile.open("TheCustomerAccount.txt");
		if (accountFile.is_open()) {
			cout << "     Customer Account Details" << endl;
			cout << " Name: " << firstName << lastName << endl;
			cout << " Email: " << emailAddress << endl;
			cout << " Phone Number: " << phoneNumber << endl;
			cout << " Username: " << userName << endl;
			cout << " Password: " << password << endl;
		}
		accountFile.close();
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
		bookingCustomer.open("CustomerReservationBookings.txt");
		cout << "To begin a new reservations booking, please enter the following details below: " << endl;
		cout << "First Name: ";
		cin >> customerFirstName;
		cout << "Last Name: ";
		cin >> customerLastName;
		cout << "# of Guest: ";
		cin >> guest;
		r.checkInDate(m, d, y);
		r.checkOutDate(m1, d1, y1);
		cout << "Packages, Would you like a special type? ";
		if (cin >> y) {
			cout << endl;
			customerRoomPackages();
		}
		else {
			cout << "The Following Rooms are below: " << endl;
		}
		// Copies Customer Booking Information to File 
		if (bookingCustomer.is_open()) {
			bookingCustomer << "            Customer Reservation Details      " << endl;
			bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
			bookingCustomer << " # of Guest During Stay : " << guest << endl;
			bookingCustomer << " Duration of Stay: " << &reservationClass::checkOutDate << " TO " << &reservationClass::checkInDate << endl; // error here bc of the r.checkInDate and r.checkout, had to update it to compile
			bookingCustomer << " Package: " << package << endl;
			if (package == 1) {
				bookingCustomer << " Single King Suite " << endl;
				bookingCustomer << " Price: $195 a night " << endl;
			}
			else if (package == 2) {
				bookingCustomer << " Double King Suite " << endl;
				bookingCustomer << " Price: $155 a night " << endl;
			}
			else if (package == 3) {
				bookingCustomer << " Deluxe Suite " << endl;
				bookingCustomer << " Price: $300 a night " << endl;
			}
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
		int p1Price = 195, p2Price = 155, p3Price = 250;
		int a1price = 10, a2price = 20, a3price = 30, a4price = 40, a5price = 60;
		// Room Packages Information 
		cout << endl;
		cout << "The Followiing Room Packages are listed below: " << endl;
		cout << endl;
		cout << "1. Single King Suite " << endl;
		cout << "Includes TV, Free Wifi, Window View " << endl;
		cout << "Price: $195 a night " << endl;
		cout << endl;
		cout << "2. Double King Suite " << endl;
		cout << "Includes TV, Free Wifi, Window View" << endl;
		cout << "Hotel Amentities Included: Pool, Breakfast" << endl;
		cout << "Price: $155 a night " << endl;
		cout << endl;
		cout << "3. Deluxe King Suite " << endl;
		cout << "Includes TV, Free Wifi, Window View, Jetted Tub, Kitchenate Area" << endl;
		cout << "Hotel Amentities Included: Pool, Hot Tub (Unlimited Use), Breakfast, Fitness Center (Unlimited Use) " << endl;
		cout << "Price: $250 a night " << endl;
		cout << endl;
		cout << "Which Package Would you like? ";
		cin >> package;
		switch (package) {
			// Single Suite Switch Casse 
		case 1:
			cout << "You've selected the Single Suite, excellent choice! " << endl;
			cout << endl;
			cout << "Would you like you to add on any amentities? " << endl;
			if (cin >> y) {
				cout << endl;
				cout << "**** Hotel Amentities Add Ons ****" << endl;
				cout << "1. Hot Tub $10 a day, Maximum use 5 days per stay " << endl;
				cout << "2. Fitness Center $10 a day, Maximum use 5 days per stay " << endl;
				cout << "Which amentities would you like to add? " << endl;
				cin >> amentityOption;
				// Single Suite Amentities Switch Case 
				switch (amentityOption)
				{
				case 1:
					cout << endl;
					cout << "**** Hot Tub *****" << endl;
					cout << "How many days would you like to us the hot tub during your stay? ";
					cin >> daysForAmen;
					if (daysForAmen == 1) {
						cout << "$10 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a1price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 1 night " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}

						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 2) {
						cout << "$20 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a2price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 2 night " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}

						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 3) {
						cout << "$30 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a3price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 3 night " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}

						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 4) {
						cout << "$40 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a4price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 4 night " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 5) {
						cout << "$50 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a5price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 5 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					break;
				case 2:
					cout << endl;
					cout << "**** Fitness Center *****" << endl;
					cout << "How many days would you like to us the fitness center during your stay? ";
					cin >> daysForAmen;
					if (daysForAmen == 1) {
						cout << "$10 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a1price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << "  Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 1 night " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
							bookingCustomer.close();
						}

						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 2) {
						cout << "$20 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a2price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 2 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
							bookingCustomer.close();
						}
						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 3) {
						cout << "$30 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a3price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 3 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
							bookingCustomer.close();
						}

						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 4) {
						cout << "$40 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a4price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 4 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
							bookingCustomer.close();
						}

						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 5) {
						cout << "$50 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p1Price + a5price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 1) {
								bookingCustomer << " Single King Suite " << endl;
								bookingCustomer << " Price: $195 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 5 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
							bookingCustomer.close();
						}

						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					break;
				default:
					break;
				}
			}
			/* End Single Suite Switch Case */
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
			break;
			// Double Suite Switch Case 
		case 2:
			cout << "You've selected the Double Suite, excellent choice! " << endl;
			cout << "Would you like you to add on any amentities? " << endl;
			if (cin >> y) {
				cout << endl;
				cout << "**** Hotel Amentities Add Ons ****" << endl;
				cout << "1. Hot Tub $10 a day, Maximum use 5 days per stay " << endl;
				cout << "2. Fitness Center $10 a day, Maximum use 5 days per stay " << endl;
				cout << "Which amentities would you like to add? " << endl;
				cin >> amentityOption;
				// Double Suite Amentities Switch Case 
				switch (amentityOption)
				{
				case 1:
					cout << endl;
					cout << "**** Hot Tub *****" << endl;
					cout << "How many days would you like to us the hot tub during your stay? ";
					cin >> daysForAmen;
					if (daysForAmen == 1) {
						cout << "$10 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a1price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 1 night " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 2) {
						cout << "$20 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a2price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 2 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 3) {
						cout << "$30 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a3price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;
						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 3 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 4) {
						cout << "$40 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a4price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;
						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 4 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 5) {
						cout << "$50 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a5price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Hot Tub for 5 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					break;
				case 2:
					cout << endl;
					cout << "**** Fitness Center *****" << endl;
					cout << "How many days would you like to us the fitness center during your stay? ";
					cin >> daysForAmen;
					if (daysForAmen == 1) {
						cout << "$10 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a1price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 1 night " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 2) {
						cout << "$20 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a2price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 2 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 3) {
						cout << "$30 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a3price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 3 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}

						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 4) {
						cout << "$40 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a4price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();
						cout << endl;

						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 4 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}

						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					else if (daysForAmen == 5) {
						cout << "$50 added to your bill" << endl;
						cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
						cout << endl;

						int total = p2Price + a5price;
						cout << "Payment Total: $" << total << endl;
						r.getPayment();


						// Adding amentities into file 
						if (bookingCustomer.is_open()) {
							bookingCustomer << "            Customer Reservation Details      " << endl;
							bookingCustomer << " Name: " << customerFirstName << customerLastName << endl;
							bookingCustomer << " # of Guest During Stay : " << guest << endl;
							bookingCustomer << " Duration of Stay: " << customerCheckIn << " TO " << customerCheckOut << endl;
							bookingCustomer << " Package: " << package << endl;
							if (package == 2) {
								bookingCustomer << " Double King Suite " << endl;
								bookingCustomer << " Price: $155 a night " << endl;
								bookingCustomer << " Hotel Amentities added: Fitness Center for 5 nights " << endl;
								bookingCustomer << " Total Price: $" << total << endl;
							}
						}
						cout << endl;
						cout << "Would you like to go back to home menu? ";
						if (cin >> y) {
							customerMenuOptionTwo();
						}
						else if (cin >> n) {
							cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
						}
					}
					break;
				default:
					break;
				}
			}
			/* End Double Suite Switch Case */
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
			break;
		case 3:
			cout << "You've selected the Deluxe Suite, the best choice! " << endl;
			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;
			cout << "Payment Total: $" << p3Price << endl;
			r.getPayment();

			cout << endl;
			cout << "Would you like to go back to home menu? ";
			if (cin >> y) {
				customerMenuOptionTwo();
			}
			else if (cin >> n) {
				cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			}
			break;
		default:
			break;
		}
	}
	// Cancel Booking Reservations
	void cancelCustomerReservation() {
		string y = "yes";
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
			}
			else if (package == 2) {
				cout << " Double King Suite " << endl;
				cout << " Price: $155 a night " << endl;
			}
			else if (package == 3) {
				cout << " Deluxe Suite " << endl;
				cout << " Price: $300 a night " << endl;
			}
		}
		cout << "Would you like to cancel your reservation? ";
		if (cin >> y) {
			cout << "Your reservation has been canceled. If you would like to create a new reservation, please go back to the home screen! " << endl;
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

		cout << endl << "***** Mo's Hotels Amentities *****" << endl;
		cout << "With your stay you have the option to enjoy the following amentities below: " << endl;
		cout << "1. Pool " << endl;
		cout << "2. Hot Tub " << endl;
		cout << "3. Breakfast " << endl;
		cout << "4. Fitness Center " << endl;
		cout << " If you want more information on each option, please select an option above ";
		cin >> selectedChoice;
		for (int i = 0; i < selectedChoice; i++) {
			switch (selectedChoice)
			{
			case 1:
				cout << endl << "******** OLYMPIC POOL ********" << endl;
				cout << "Our pool is an olympic size pool and is free to all guest. " << endl;
				cout << "Located: 2nd Floor " << endl;
				cout << "To use the pool just scan your room card! " << endl;
				cout << "Thank you!!!!" << endl;
				cout << endl;
				cout << "Would you like to go back to home menu? ";
				if (cin >> y) {
					customerMenuOptionTwo();
				}
				else if (cin >> n) {
					cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
				}
				break;
			case 2:
				cout << endl << "******** HOT TUB ********" << endl;
				cout << "Our hot tubs are included in the Deluxe Suite Package! However we do offer day passes for hotel guest who have NOT selected the deluxe suite. " << endl;
				cout << "Day Pass Price: $10 a day " << endl;
				cout << "If you would like to purchase a day pass, please go to reservation page. " << endl;
				cout << "Thank You!!!" << endl;
				cout << endl;
				cout << "Would you like to go back to home menu? ";
				if (cin >> y) {
					customerMenuOptionTwo();
				}
				else if (cin >> n) {
					cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
				}
				break;
			case 3:
				cout << endl << "******* Breakfast ********" << endl;
				cout << " We offer complintary breakfast for our guest 7 days a week. " << endl;
				cout << "Days: Monday - Sunday" << endl;
				cout << "Time: " << endl;
				cout << "Monday - Thursday: 6am - 9am " << endl;
				cout << "Friday - Sunday: 7am - 10 am " << endl;
				cout << endl;
				cout << "Would you like to go back to home menu? ";
				if (cin >> y) {
					customerMenuOptionTwo();
				}
				else if (cin >> n) {
					cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
				}
				break;
			case 4:
				cout << endl << "******** Fitness Center ******** " << endl;
				cout << "Our fitness centers is included in the Deluxe suite package, however day passes are available! " << endl;
				cout << "Day Pass Price: $10 a day " << endl;
				cout << "If you would like to purchase a day pass, please go to reservation page. " << endl;
				cout << "Thank You!!!" << endl;
				cout << endl;
				cout << "Would you like to go back to home menu? ";
				if (cin >> y) {
					customerMenuOptionTwo();
				}
				else if (cin >> n) {
					cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
				}
				break;
			default:
				break;
			}
		}
	}
};
