#include <iostream>
#include <sstream>
#include <string>
#include <mysql.h>	// Database connection
#include <map>	   
#include <vector>
#include "ConnectionProperties.h" // Database connection string
using namespace std;

class HotelDB
{
public:

	void setQuery(string storedProcedure) {
		if (storedProcedure.empty())
		{
			throw 0;
		}
		_query = "";
		_query += storedProcedure;
	}

	map <string, string> getCustomerData()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			map <string, string> cInfo;
			int qstate;

			startConnection();

			// Call the stored procedure from the database
			const char* q = _query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Connection to HotelSystemDB failed.");
			}

			res = mysql_store_result(conn);

			int num_Fields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				// Create a dictionary to house the data we will retrieve from the database
				cInfo = {
					{"CustomerID"   , ""},
					{"FirstName"	, ""},
					{"LastName"		, ""},
					{"UserName"	    , ""},
					{"Password"	    , ""},
					{"PhoneNumber"  , ""},
					{"EmailAddress" , ""},
					{"RewardsPoints", ""}
				};

				for (int i = 0; i < num_Fields; i++)
				{
					if (row[i] != nullptr)
					{
						cInfo[fields[i].name] = row[i];
					}
				}
			}

			return cInfo;
		}
		catch (exception e)
		{
			throw exception("Error connecting to database.");
		}
	}

	map <string, string> getEmployeeData()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			map <string, string> eInfo;
			int qstate;

			startConnection();

			// Call the stored procedure from the database
			const char* q = _query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Query error.");
			}

			res = mysql_store_result(conn);

			int numOfFields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				// Create a dictionary to house the data we will retrieve from the database
				eInfo = {
					{"EmployeeID"   , ""},
					{"FirstName"	, ""},
					{"LastName"		, ""},
					{"UserID"	    , ""},
					{"Password"	    , ""},
				};

				for (int i = 0; i < numOfFields; i++)
				{
					eInfo[fields[i].name] = row[i];

				}
			}

			return eInfo;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getReservations(int customerID)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the reservations
			vector<map<string, string>> allCustomerReservations;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> rInfo = {
				{"ReservationID"	 , ""},
				{"PackageID"		 , ""},
				{"PackageTypeID"	 , ""},
				{"PackageName"		 , ""},
				{"BaseCost"			 , ""},
				{"AmenityName"		 , ""},
				{"AddOnDays"		 , ""},
				{"TotalCost"		 , ""},
				{"FirstName"		 , ""},
				{"LastName"			 , ""},
				{"NumberOfGuests"	 , ""},
				{"CheckInDate"	     , ""},
				{"CheckOutDate"	     , ""},
			};

			// Connect to Database
			startConnection();


			// Call the stored procedure from the database
			string query = "CALL GetReservations(" + to_string(customerID) + ")";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Query error.");
			}

			res = mysql_store_result(conn);

			int numOfFields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				for (int i = 0; i < numOfFields; i++)
				{
					if (row[i] != nullptr)
						rInfo[fields[i].name] = row[i];
				}

				allCustomerReservations.push_back(rInfo);
				rInfo.clear();
			}

			return allCustomerReservations;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getPackageTypes()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the package types
			vector<map<string, string>> allPackageTypes;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> ptInfo = {
				{"PackageTypeID"	,		""},
				{"PackageName"	,			""},
				{"PackageDescription",		""},
				{"Amentities",				""},
				{"BaseCost",				""},
				{"Available",				""},
				{"UnderMaintenance",		""}
			};

			// Connect to Database
			startConnection();

			// Call the stored procedure from the database
			string query = "CALL GetPackageTypes()";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Query error.");
			}
			res = mysql_store_result(conn);

			int numOfFields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				for (int i = 0; i < numOfFields; i++)
				{
					if (row[i] != nullptr)
						ptInfo[fields[i].name] = row[i];
				}

				allPackageTypes.push_back(ptInfo);
				ptInfo.clear();
			}
			return allPackageTypes;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getAddons()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the addons
			vector<map<string, string>> allAddons;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> addInfo = {
			{ "AddOnID"	,				"" },
			{ "AmenityName"	,			"" },
			{ "AmenityDescription",		"" },
			{ "BaseCost",				"" }
			};

			// Connect to Database
			startConnection();

			// Call the stored procedure from the database
			string query = "CALL GetAddons()";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Query error.");
			}
			res = mysql_store_result(conn);

			int numOfFields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				for (int i = 0; i < numOfFields; i++)
				{
					if (row[i] != nullptr)
						addInfo[fields[i].name] = row[i];
				}

				allAddons.push_back(addInfo);
				addInfo.clear();
			}


			return allAddons;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getHotelAmenities()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the addons
			vector<map<string, string>> allAmenities;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> aInfo = {
				{"AmenityName"	,			""},
				{"AmenityDescription",		""},
				{"Auxiliary1"	,			""},
				{"Auxiliary2"	,			""},
				{"Auxiliary3"	,			""},
				{"Auxiliary4"	,			""},
				{"Auxiliary5"	,			""},
			};

			// Connect to Database
			startConnection();

			// Call the stored procedure from the database
			string query = "CALL GetHotelAmenities()";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Query error.");
			}
			res = mysql_store_result(conn);

			int numOfFields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				for (int i = 0; i < numOfFields; i++)
				{
					if (row[i] != nullptr)
						aInfo[fields[i].name] = row[i];
				}

				allAmenities.push_back(aInfo);
				aInfo.clear();
			}


			return allAmenities;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}
	
	vector<map<string, string>> getEligibleRewards(int customerID)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the Rewards Rewards
			vector<map<string, string>> allRewards;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> rInfo = {
				{"RewardID",			""},
				{"RewardName",			""},
				{"RewardDescription",	""},
				{"RequiredRewards",		""}
			};

			// Connect to Database
			startConnection();

			// Call the stored procedure from the database
			string query = "CALL GetEligibleRewards(" + to_string(customerID) + ")";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Query error.");
			}
			res = mysql_store_result(conn);

			int numOfFields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				for (int i = 0; i < numOfFields; i++)
				{
					if (row[i] != nullptr)
						rInfo[fields[i].name] = row[i];
				}

				allRewards.push_back(rInfo);
				rInfo.clear();
			}

			return allRewards;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getSummaryReport()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the package types
			vector<map<string, string>> summaryReport;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> ptInfo = {
				{"numReservations"	,		""},
				{"numRoomsAvailable"	,		""},
				{"numUnderMaintenance",		""},
			};

			// Connect to Database
			startConnection();

			// Call the stored procedure from the database
			string query = "CALL SummaryReport()";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			
			if (qstate)
			{
				throw exception("Query error.");
			}

			res = mysql_store_result(conn);

			int numOfFields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				for (int i = 0; i < numOfFields; i++)
				{
					if (row[i] != nullptr)
						ptInfo[fields[i].name] = row[i];
				}

				summaryReport.push_back(ptInfo);
				ptInfo.clear();
			}

			return summaryReport;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	bool saveToDatabase()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			int qstate;

			startConnection();

			const char* q = _query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Query error.");
			}

			res = mysql_store_result(conn);
			return true;
		}
		catch (exception e)
		{
			throw exception("Error connecting to the database.");
		}
	}

private:
	MYSQL* conn;
	string _query = "";

	void startConnection() {
		try
		{
			int qstate;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0);

			if (!conn)
			{
				throw exception("Connection error.");
			}

			cout << endl << "Connection to MySQL successful, connecting to HotelSystemDB..." << endl;

			// Check if the database exists
			string query = "USE HotelSystemDB;";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (qstate)
			{
				throw exception("Connection to HotelSystemDB failed.");
			}

		}
		catch (exception e)
		{
			cout << "Error connecting to database" << endl;
		}
	}

};

class MenuHelper
{
private:
	bool _exitProgram = false;
	bool _zeroItemSelected = false;
public:
	int selectedItem = 0;

	// Interface Menus
	void printMenu(string titleText, int menuSize, string menuOptions[], string instructionText)
	{
		selectedItem = 0;
		bool continueToNextMenu = false;
		
		do {
			// Display the menu text
			cout << "**************************************" << endl;
			cout << "\t" << titleText << endl;
			cout << "**************************************" << endl;
			for (int i = 0; i < menuSize; i++)
			{
				cout << "     " << i + 1 << ". " << menuOptions[i] << " " << endl;
			}

			// Get the Selected Item
			selectedItem = menuOptionCheck(menuSize, instructionText);
			continueToNextMenu = selectedItem != 0;

			if (_zeroItemSelected || _exitProgram)
			{
				break;
			}

		} while (!continueToNextMenu);
	}

	bool returnToMenu()
	{
		cout << "Would you like to go back to the home screen? ";
		string y = "yes";
		cin >> y;

		if (y == "yes") {
			return true;
		}
		cout << "Thank you for choicing Mo's Hotel we look forward to serving you in the future! " << endl;
		return false;
	}
	
	int menuOptionCheck(int menuSize, string message)
	{

		cout << message << endl;
		cin >> selectedItem;

		_zeroItemSelected = selectedItem == 0;
		_exitProgram = cin.fail();

		if (_zeroItemSelected) {
			return 0;
		}

		if (_exitProgram) {
			return 0;
		}

		while (selectedItem > menuSize)
		{
			cout << message << endl;
			cin >> selectedItem;
		}

		return selectedItem;
	}

	bool checkLength(string text, int maxLength)
	{
		if (text.length() > maxLength || text.length() < maxLength)
		{
			return false;
		}
		return true;
	}
};
