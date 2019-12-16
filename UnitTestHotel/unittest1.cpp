#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Hotel-Management-System-Software--Database-Setup/ConnectionProperties.h"
#include "../Hotel-Management-System-Software--Database-Setup/Database.h"
#include "../Hotel-Management-System-Software--Database-Setup/Customer.h"
#include "../Hotel-Management-System-Software--Database-Setup/Employee.h"
#include "../Hotel-Management-System-Software--Database-Setup/Reservartions.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHotel
{
	TEST_CLASS(LoginTests)
	{
	public:

		TEST_METHOD(CustomerLogin)
		{
			// Arrange
			userCustomer c;
			MenuHelper mh;
			string userName = "csamano1";
			string password = "csaman";

			// Act
			bool userNameLengthCheck = mh.checkLength("csamano1", 8);
			bool passwordLengthCheck = mh.checkLength("csaman", 6);
			c.getCustomerData("csamano1", "csaman");

			// Assert
			Assert::IsTrue(userNameLengthCheck);
			Assert::IsTrue(passwordLengthCheck);
			Assert::IsTrue(c.customerDataLoaded);
		}

		TEST_METHOD(CreateCustomerAccounts)
		{
			// Arrange
			userCustomer c;
			MenuHelper mh;
			string userName = "testne23";
			string password = "testnw";
			string firstName = "TestNewName";
			string lastName = "ForUnitTest";
			string emailAddress = "TestNewName@Yahoo.com";
			string phoneNumber = "3138674025";

			// Act
			bool userNameLengthCheck = mh.checkLength(userName, 8);
			bool passwordLengthCheck = mh.checkLength(password, 6);
			c.saveCustomerData(userName, password, firstName, lastName, emailAddress, phoneNumber);

			// Assert
			Assert::IsTrue(userNameLengthCheck);
			Assert::IsTrue(passwordLengthCheck);
			Assert::IsTrue(c.customerSaved);
		}

		TEST_METHOD(EmployeeLogin)
		{
			// Arrange
			employeeClass e;
			MenuHelper mh;
			// Act
			bool userNameLengthCheck = mh.checkLength("1232", 4);
			bool passwordLengthCheck = mh.checkLength("csaman", 6);
			e.getEmployeeData("1234", "csaman");

			// Assert
			Assert::IsTrue(userNameLengthCheck);
			Assert::IsTrue(passwordLengthCheck);
			Assert::IsTrue(e.employeeDataLoaded);
		}

		TEST_METHOD(CreateEmployeeAccounts)
		{
			// Arrange
			employeeClass e;
			MenuHelper mh;
			string userID = "2263";
			string password = "testnw";
			string firstName = "TestNewName";
			string lastName = "ForUnitTest";

			// Act
			bool userNameLengthCheck = mh.checkLength(userID, 4);
			bool passwordLengthCheck = mh.checkLength(password, 6);
			e.saveEmployeeData(userID, password, firstName, lastName);

			// Assert
			Assert::IsTrue(userNameLengthCheck);
			Assert::IsTrue(passwordLengthCheck);
			Assert::IsTrue(e.employeeSaved);
		}
	};

	TEST_CLASS(ReservationTests)
	{
	public:
		
		TEST_METHOD(CustomerReservation)
		{
			// Arrange
			userCustomer c;
			HotelDB hotel;
			reservationClass res;
			int package;
			int guest = 6;
			string customerCheckIn = "10/10/2019", customerCheckOut = "12/03/2019";
			string userName = "csamano1";
			string password = "csaman";
			vector<map<string, string>> allPackageInfo;
			map<string, string> selectedPackage;
			vector<map<string, string>> allAddonInfo;
			map<string, string> selectedAddon;
			int amentityOption = 0;
			int daysForAmen = 4;
			int total = 0;
			int adjustedRewards = c.currentRewards;

			// Act
			c.getCustomerData(userName, password);

			allPackageInfo = hotel.getPackageTypes(); // Packages are removed when they get booked, so this will return null after packagesTypes-1 is 0
			allPackageInfo = hotel.getPackageTypes(); // Packages are removed when they get booked, so this will return null after packagesTypes-1 is 0
			package = 1;
			selectedPackage = allPackageInfo[package - 1];


			allAddonInfo = hotel.getAddons();
			amentityOption = 2;
			selectedAddon = allAddonInfo[amentityOption - 1];

			total = stoi(selectedPackage["BaseCost"]) + (stoi(selectedAddon["BaseCost"]) * daysForAmen);

			adjustedRewards += total;
			res.saveReservation(c.customerID, guest, customerCheckIn, customerCheckOut, selectedPackage["PackageTypeID"], selectedAddon["AddOnID"], daysForAmen, total, adjustedRewards, 0, 0);

			// Assert
			Assert::IsTrue(c.customerDataLoaded);
			Assert::IsTrue(res.reservationSaved);
		}

		TEST_METHOD(CustomerCancelReservationTest)
		{
			// Arrange
			reservationClass res;
			HotelDB hotel;
			userCustomer c;
			string userName = "testnew2";
			string password = "testnw";
			int selectedRes = 1;
			vector<map<string, string>> allReservationInfo;
			map<string, string> selectedReservation;

			// Act
			c.getCustomerData(userName, password);
			if (c.customerDataLoaded)
			{
				allReservationInfo = hotel.getReservations(c.customerID);
				if (!allReservationInfo.empty()) {
					selectedReservation = allReservationInfo[selectedRes - 1];
					res.cancelReservation(c.customerID, stoi(selectedReservation["ReservationID"]));
				}
			}

			// Assert
			if (allReservationInfo.empty()) 
			{
				Assert::IsFalse(res.foundRes);
			}
			else {
				Assert::IsTrue(res.reservationCancelled);
			}
		}

		TEST_METHOD(EmployeeCancelsReservationtTest)
		{
			// Arrange
			reservationClass res;
			HotelDB hotel;
			employeeClass e;
			string cFirstName = "Cindy";
			string cLastName = "samano";
			string phoneNumber = "(313)693-0987";
			map<string, string> selectedReservation;
			int selectedRes = 1;
			map <string, string> cInfo;
			int customerID = 0;
			vector<map<string, string>> allReservationInfo;

			// Act
			hotel.setQuery("SELECT CustomerID FROM Customer WHERE FirstName = '" + cFirstName + "'and LastName = '" + cLastName + "' and PhoneNumber = '" + phoneNumber + "';");
			cInfo = hotel.getCustomerData();

			if (!cInfo.empty()) {
				customerID = stoi(cInfo["CustomerID"]);
				allReservationInfo = hotel.getReservations(customerID);
				map<string, string> selectedReservation = allReservationInfo[selectedRes-1];
				res.cancelReservation(customerID, 40);
			}

			// Assert
			Assert::IsTrue(res.reservationCancelled);
		}

		TEST_METHOD(EmployeeEditsReservationTest)
		{
			// Arrange
			reservationClass res;
			HotelDB hotel;
			employeeClass e;
			map<string, string> selectedReservation;
			int selected = 1;
			map <string, string> cInfo;
			int customerID = 0;
			vector<map<string, string>> allReservationInfo;

			// Act
			allReservationInfo = hotel.getReservations(2);
			map<string, string> selectedRes = allReservationInfo[selected - 1];
			string reservationID = selectedRes["ReservationID"];

			hotel.setQuery("UPDATE Reservation SET NumberOfGuests = 34  WHERE ReservationID = " + reservationID);
			e.editComplete = hotel.saveToDatabase();

			hotel.setQuery("UPDATE Reservation SET CheckInDate = '01/01/01' , CheckOutDate = '01/01/01' WHERE ReservationID = " + reservationID);
			e.editComplete = hotel.saveToDatabase();

			// Assert
			Assert::IsTrue(e.editComplete);
		}


		TEST_METHOD(EmployeeSummaryReportTest)
		{

			// Arrange
			HotelDB hotel;
			vector<map<string, string>> summaryReport;

			// Act
			summaryReport = hotel.getSummaryReport();

			// Assert
			Assert::IsTrue(!summaryReport.empty());
		}


		TEST_METHOD(CustomerRewardsTest)
		{

			// Arrange
			HotelDB hotel;
			userCustomer c;
			vector<map<string, string>> eligibleRewards;
			map<string, string> selectedReward;
			bool saved = false;
			int requiredRewards, adjustedRewards = 0;

			// Act
			c.getCustomerData("csaman90", "csaman");
			eligibleRewards = hotel.getEligibleRewards(c.customerID);
			
			if (!eligibleRewards.empty()) {
				selectedReward = eligibleRewards[0];
				requiredRewards = stoi(selectedReward["RequiredRewards"]);
				adjustedRewards = c.currentRewards - requiredRewards;

				hotel.setQuery("CALL UpdateRewards(" + to_string(c.customerID) + "," + to_string(adjustedRewards) + ")");
				saved = hotel.saveToDatabase();
			}
			// Assert
			Assert::IsTrue(saved);
		}



	};


	TEST_CLASS(HotelDataTests)
	{
	public:
		TEST_METHOD(SetQueryTest)
		{

			auto  expPtr = [this] {
				// Arrange
				HotelDB hotel;
				string testEmpty; 
				
				// Act
				hotel.setQuery(testEmpty);  };
			

			// Assert
			Assert::ExpectException<int>(expPtr);
		}

		TEST_METHOD(HotelDataTest)
		{
			// Arrange
			HotelDB hotel;
			vector<map<string, string>> getPackageTypes;
			vector<map<string, string>> getAddons;
			vector<map<string, string>> getHotelAmenities;
			vector<map<string, string>> getEligibleReward;
			bool allLoaded = false;

			// Act
			getPackageTypes = hotel.getPackageTypes();
			getAddons = hotel.getAddons();
			getHotelAmenities = hotel.getHotelAmenities();
			getEligibleReward = hotel.getEligibleRewards(2);

			if (!getPackageTypes.empty() && !getAddons.empty() && !getHotelAmenities.empty() || !getEligibleReward.empty())
			{
				allLoaded = true;
			}

			// Assert
			Assert::IsTrue(allLoaded);
		}
	};

}