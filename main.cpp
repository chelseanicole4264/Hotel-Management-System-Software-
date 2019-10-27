/* Names: Chelsea S., Chris D., Chris J, Cindy S. 
Project Purpose: Hotel Management System 
Start Date: 7/25/2019
Modification Date: 10/24/2019
*/

#include <iostream>
#include <string>
#include <fstream>
// Classes 
#include "Employee.h"
#include "Customer.h"
#include "Reservartions.h"
#include <mysql.h> // Need for Database connection
using namespace std; 

// Main File for Employee Login/Menu Options and Customer Login/Menu Options

// Employee Interface Screen 
// Customer Interface Screen 
void customerMenuOptionOne() {
	userCustomer customer;
	int num;
	cout << "**************************************" << endl;
	cout << "    Welcome to Mo's Hotel System      " << endl;
	cout << "**************************************" << endl;
	cout << "     1. Create Account" << endl;
	cout << "     2. Login to System" << endl;
	cout << " Please make a choice:" << endl;
	cin >> num;

	for (int i = 0; i < num; i++) {
		switch (num) {
		case 1:
			customer.customerCreateAccount();
			break;
		case 2:
			customer.customerLogin();
			break;
		default:
			break;
		}
	}
}


void testDatabaseConnection() 
{
	/*
	CREATE DATABASE testdb;
	USE testdb;
	CREATE TABLE test (id int, name varchar(32), score int);
	INSERT INTO test (id, name, score) VALUES (1, "Marianne", 89);
	INSERT INTO test (id, name, score) VALUES (2, "Jimmy", 62);
	INSERT INTO test (id, name, score) VALUES (3, "Ling", 78);
	SELECT * FROM test;
	*/

	try
	{
		MYSQL* conn;
		MYSQL_RES * res;
		MYSQL_ROW row;
		int qstate;

		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "MySQLPassword1", "testdb", 3306, NULL, 0); // use your localhost password

		if (conn) // failing here, jk I had to add-in my localhost password
		{
			cout << "Connection Successful" << endl;

			string query = "SELECT * FROM test"; // run the sql script above to create a test table in the database

			const char* q = query.c_str();

			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
				}

				cout << endl;
			}
			else 
			{
				cout << "Query Failed" << endl;
			}
		}
		else
		{
			cout << "Connection failed, check parameters in mysql_real_connect()" << endl;
		}
	}
	catch (exception e) 
	{
		cout << "Error connecting to database" << endl;
	}
}

int main() {
	int num, num2;
	employeeClass e;

	// Test Database Connection
	testDatabaseConnection();

	// Hotel Main Screen 
	cout << "**************************************" << endl;
	cout << "      Welcome to Mo's Hotel           " << endl;
	cout << "   Where we Value our Customers       " << endl;
	cout << "**************************************" << endl;
	cout << endl;

	cout << "Are you a Cutomer or Employee?." << endl << "0. Customer" << endl << "1. Employee" << endl;
	cin >> num2;
	while (num2 > 1 || num2 < 0)
	{
		cout << "Invalid respose. Please enter 0 for customer or 1 for employee." << endl;
		cin >> num2;
	}
	if (num2 == 1)
	{
		cout << "Do you have an Employee account?" << endl << "Press 0 for Yes" << endl << "Press 1 for No ";
		cin >> num;
		while (num > 1 || num < 0)
		{
			cout << "Invalid respose. Please enter 0 for yes or 1 for no." << endl;
			cin >> num;
		}
		switch (num) {
		case 0:
			cout << "Great! Directing you to the Login..." << endl;//Goes to login screen
			e.employeeLogin();
			break;
		case 1:
			cout << endl << "Create an Account Please" << endl;//Goes to create account
			e.employeeCreateAccount();
			break;
		}
	}
	else if (num2 == 0)
	{
		customerMenuOptionOne();

	}
	system("pauase");
	return 0;
}