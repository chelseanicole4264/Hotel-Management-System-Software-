#include <iostream>
#include <string>
#include <fstream>
#include <mysql.h>	// Database connection
#include <map>	   
#include <vector>
using namespace std;

class HotelDB
{
public:

	HotelDB()
	{	
		startConnection();
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

			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetReservations(" + to_string(customerID) + ")";
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
							if (row[i] != nullptr)
								rInfo[fields[i].name] = row[i];
						}

						allCustomerReservations.push_back(rInfo);
						rInfo.clear();
					}					
				}
				else
				{
					cout << "Unable to retrieve your reservations." << endl;
				}
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
				{"BaseCost",				""}
			};

			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetPackageTypes()";
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
							if(row[i] != nullptr)
								ptInfo[fields[i].name] = row[i];
						}
						
						allPackageTypes.push_back(ptInfo);
						ptInfo.clear();
					}
				}
				else
				{
					cout << "Packages unavailable." << endl;
				}
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
				{"AddOnID"	,			""},
				{"AmenityName"	,			""},
				{"AmenityDescription",		""},
				{"BaseCost",				""}
			};

			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetAddons()";
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
							if (row[i] != nullptr)
								addInfo[fields[i].name] = row[i];
						}

						allAddons.push_back(addInfo);
						addInfo.clear();
					}

				}
				else
				{
					cout << "Amentities unavailable." << endl;
				}
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

			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetHotelAmenities()";
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
							if (row[i] != nullptr)
								aInfo[fields[i].name] = row[i];
						}

						allAmenities.push_back(aInfo);
						aInfo.clear();
					}

				}
				else
				{
					cout << "Amentities unavailable." << endl;
				}
			}

			return allAmenities;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	bool customerExists() { return customerSaved || hasCustomerData; }

	bool employeeExists() { return employeeSaved || hasEmployeeData; }
	
	void startConnection() {
		try
		{
			int qstate;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn, "localhost", "root", "MySQLPassword1", "HotelSystemDB", 3306, NULL, 0); // use your localhost password

			if (conn)
			{
				cout << "Connection to MySQL successful, connecting to HotelSystemDB..." << endl;

				// Check if the database exists
				string query = "USE HotelSystemDB;";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << "Connection to HotelSystemDB successful." << endl;
					cout << endl;
				}
				else
				{
					cout << "Connection to HotelSystemDB failed." << endl;
				}
			}
		}
		catch (exception e)
		{
			cout << "Error connecting to database" << endl;
		}
	}

private:
	MYSQL* conn;
	bool customerSaved = false;
	bool employeeSaved = false;
	bool reservationBooked = false;

	bool hasCustomerData = false;
	bool hasEmployeeData = false;
	bool hasReservation = false;

	
};