
    CREATE DATABASE IF NOT EXISTS HotelSystemDB;
	USE HotelSystemDB;

-- START CREATE TABLES SECTION-----------------------------    
	CREATE TABLE IF NOT EXISTS Employee (EmployeeID int(4) NOT NULL AUTO_INCREMENT, FirstName varchar(100), LastName varchar(100), Password varchar(6), CONSTRAINT employee_id PRIMARY KEY(EmployeeID));

    CREATE TABLE IF NOT EXISTS Customer (CustomerID int(4) NOT NULL AUTO_INCREMENT, FirstName varchar(100), LastName varchar(100), UserName varchar(8), Password varchar(6), PhoneNumber varchar(13), EmailAddress varchar(100),  RewardsPoints int,
    CONSTRAINT customer_id PRIMARY KEY(CustomerID));
    
    CREATE TABLE IF NOT EXISTS PackageType (PackageTypeID int NOT NULL AUTO_INCREMENT, Code varchar(100), PackageDescription varchar(200), BaseCost int, 
    CONSTRAINT packageType_id PRIMARY KEY(PackageTypeID) );
    
    CREATE TABLE IF NOT EXISTS AddOn (AddOnID int NOT NULL AUTO_INCREMENT,  Code varchar(100), AmenityDescription varchar(200), BaseCost int, 
    CONSTRAINT addOn_id PRIMARY KEY(AddOnID) );
    
	CREATE TABLE IF NOT EXISTS Package (PackageID int NOT NULL AUTO_INCREMENT, CustomerID int(4) NOT NULL, PackageTypeID int, AddOnID int, Days int(1), TotalCost varchar(150),  
    INDEX customer_id(CustomerID),
	INDEX packageType_id(PackageTypeID),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)  ON UPDATE CASCADE ON DELETE RESTRICT, -- delect restrict prevents orphan children
    FOREIGN KEY (PackageTypeID) REFERENCES PackageType(PackageTypeID)  ON UPDATE CASCADE ON DELETE RESTRICT, 
    CONSTRAINT customer_package_id PRIMARY KEY(PackageID) );
    
	CREATE TABLE IF NOT EXISTS Reservation (ReservationID int NOT NULL AUTO_INCREMENT, CustomerID int(4) NOT NULL, PackageID int, NumberOfGuests int, CheckInDate varchar(10), CheckOutDate varchar(10),  
    INDEX customer_id(CustomerID),
    INDEX package_id(PackageID), 
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)  ON UPDATE CASCADE ON DELETE RESTRICT, 
    FOREIGN KEY (PackageID) REFERENCES Package(PackageID) ON UPDATE CASCADE ON DELETE RESTRICT, -- can't delete a parent row if a child exists, leaves no orphans behind
    CONSTRAINT customer_reservation_id PRIMARY KEY(ReservationID) );

-- END CREATE TABLES SECTION-----------------------------   


-- START INSERT TABLES SECTION-----------------------------
	INSERT IGNORE INTO Employee (FirstName, LastName, Password) VALUES ( "Cindy", "0", "pass0");
	INSERT IGNORE INTO Employee (FirstName, LastName, Password) VALUES ( "Chris", "1", "pass1");
	INSERT IGNORE INTO Employee (FirstName, LastName, Password) VALUES ( "Chris", "2", "pass2");
	INSERT IGNORE INTO Employee (FirstName, LastName, Password) VALUES ( "Chelsea", "3", "pass3");
    
    INSERT IGNORE INTO Customer (FirstName, LastName, UserName, Password, PhoneNumber, EmailAddress, RewardsPoints) VALUES ("Tom", "Holland", "Spiderman", "Webslinger", "(313) 897-9023", "friendlyNeighbor@gmail.com", 0);
    Set @CustomerID = LAST_INSERT_ID();
    
    INSERT IGNORE INTO AddOn (Code, AmenityDescription, BaseCost) VALUES ("HOT_TUB", "Hot Tub $10 a day, Maximum use 5 days per stay", 10);
    INSERT IGNORE INTO AddOn (Code, AmenityDescription, BaseCost) VALUES ("FITNESS", "Fitness Center $10 a day, Maximum use 5 days per stay", 10);
	Set @AddOnID = LAST_INSERT_ID();
    
    INSERT IGNORE INTO PackageType (Code, PackageDescription, BaseCost) VALUES ("SINGLE_KING", "Single King Suite", 195);
    INSERT IGNORE INTO PackageType (Code, PackageDescription, BaseCost) VALUES ("DOUBLE_KING", "Double King Suite", 155);
    INSERT IGNORE INTO PackageType (Code, PackageDescription, BaseCost) VALUES ("DELUXE_KING", "Deluxe King Suite", 250);
    Set @PackageTypeID = LAST_INSERT_ID();
     
	INSERT IGNORE INTO Package (CustomerID, PackageTypeID, AddOnID , Days, TotalCost) VALUES (@CustomerID, @PackageTypeID, @AddOnID, 4, "$260.00");
    Set @PackageID = LAST_INSERT_ID();
    
    INSERT IGNORE INTO Reservation (CustomerID, PackageID, NumberOfGuests, CheckInDate, CheckOutDate) VALUES (@CustomerID, @PackageID, 4, "10/27/2019", "11/04/2019");

	/*CREATE TABLE IF NOT EXISTS Maintenance (MaintenanceID int, name varchar(32), score int);
		INSERT IGNORE INTO Maintenance (MaintenanceID, name, score) VALUES (3, "Ling", 78);

	CREATE TABLE IF NOT EXISTS Summary (SummaryID int, name varchar(32), score int);
		INSERT IGNORE INTO Summary (SummaryID, name, score) VALUES (3, "Ling", 78);*/
        
        -- Table for packages foreign key reservationID and  Amentities table?

-- END INSERT TABLES SECTION-----------------------------


use hotelSystemdb;

Select * from addon;
select * from packagetype;
select * from customer;
select * from employee;
Select * from package;
select * from reservation;