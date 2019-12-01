CREATE DATABASE `hotelsystemdbTest`;

CREATE TABLE `addon` (
  `AddOnID` int(11) NOT NULL AUTO_INCREMENT,
  `AmenityName` varchar(100) DEFAULT NULL,
  `AmenityDescription` varchar(200) DEFAULT NULL,
  `BaseCost` int(11) DEFAULT NULL,
  PRIMARY KEY (`AddOnID`)
);

CREATE TABLE `customer` (
  `CustomerID` int(4) NOT NULL AUTO_INCREMENT,
  `FirstName` varchar(100) DEFAULT NULL,
  `LastName` varchar(100) DEFAULT NULL,
  `UserName` varchar(8) DEFAULT NULL,
  `Password` varchar(6) DEFAULT NULL,
  `PhoneNumber` varchar(13) DEFAULT NULL,
  `EmailAddress` varchar(1000) DEFAULT NULL,
  `RewardsPoints` int(11) DEFAULT '0',
  PRIMARY KEY (`CustomerID`)
) ;

CREATE TABLE `employee` (
  `EmployeeID` int(4) NOT NULL AUTO_INCREMENT,
  `FirstName` varchar(100) DEFAULT NULL,
  `LastName` varchar(100) DEFAULT NULL,
  `UserID` int(11) DEFAULT NULL,
  `Password` varchar(6) DEFAULT NULL,
  PRIMARY KEY (`EmployeeID`)
) ;

CREATE TABLE `package` (
  `PackageID` int(11) NOT NULL AUTO_INCREMENT,
  `PackageTypeID` int(11) DEFAULT NULL,
  `AddOnID` int(11) DEFAULT NULL,
  `AddOnDays` int(1) DEFAULT NULL,
  `TotalCost` int(11) DEFAULT NULL,
  PRIMARY KEY (`PackageID`),
  KEY `packageType_id` (`PackageTypeID`),
  CONSTRAINT `package_ibfk_1` FOREIGN KEY (`PackageTypeID`) REFERENCES `packagetype` (`PackageTypeID`) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE `packagetype` (
  `PackageTypeID` int(11) NOT NULL AUTO_INCREMENT,
  `PackageName` varchar(100) DEFAULT NULL,
  `PackageDescription` varchar(200) DEFAULT NULL,
  `Amentities` varchar(500) DEFAULT NULL,
  `BaseCost` int(11) DEFAULT NULL,
  PRIMARY KEY (`PackageTypeID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `reservation` (
  `ReservationID` int(11) NOT NULL AUTO_INCREMENT,
  `CustomerID` int(4) NOT NULL,
  `PackageID` int(11) DEFAULT NULL,
  `NumberOfGuests` int(11) DEFAULT NULL,
  `CheckInDate` varchar(10) DEFAULT NULL,
  `CheckOutDate` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`ReservationID`),
  KEY `customer_id` (`CustomerID`),
  KEY `package_id` (`PackageID`),
  CONSTRAINT `reservation_ibfk_1` FOREIGN KEY (`CustomerID`) REFERENCES `customer` (`CustomerID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `reservation_ibfk_2` FOREIGN KEY (`PackageID`) REFERENCES `package` (`PackageID`) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE `rewardBenefits` (
  `BenefitID` int(11) NOT NULL AUTO_INCREMENT,
  `BenefitName` varchar(255) DEFAULT NULL,
  `BenefitDescription` varchar(255) DEFAULT NULL,
  `RequiredRewards` int DEFAULT NULL,
  PRIMARY KEY (`BenefitID`));

-- START INSERT TABLES SECTION-----------------------------
	INSERT IGNORE INTO Employee (FirstName, LastName, UserId, Password) VALUES ( "Cindy", "0",	 1, "pass0");
	INSERT IGNORE INTO Employee (FirstName, LastName, UserId, Password) VALUES ( "Chris", "1",	 2, "pass1");
	INSERT IGNORE INTO Employee (FirstName, LastName, UserId, Password) VALUES ( "Chris", "2",	 3, "pass2");
	INSERT IGNORE INTO Employee (FirstName, LastName, UserId, Password) VALUES ( "Chelsea", "3", 4, "pass3");
    
    INSERT IGNORE INTO Customer (FirstName, LastName, UserName, Password, PhoneNumber, EmailAddress, RewardsPoints) VALUES ("Tom", "Holland", "Spiderman", "Webslinger", "(313) 897-9023", "friendlyNeighbor@gmail.com", 0);
    Set @CustomerID = LAST_INSERT_ID();
    
    INSERT IGNORE INTO AddOn (AmenityName, AmenityDescription, BaseCost) VALUES ("Hot Tub", "Hot Tub $10 a day, Maximum use 5 days per stay", 10);
    INSERT IGNORE INTO AddOn (AmenityName, AmenityDescription, BaseCost) VALUES ("Fitness Center", "Fitness Center $10 a day, Maximum use 5 days per stay", 10);
	Set @AddOnID = LAST_INSERT_ID();
    
    INSERT IGNORE INTO PackageType (PackageName, PackageDescription, Amentities, BaseCost) VALUES ("Single King Suite", "TV, Free Wifi, Window View", null, 195);
    INSERT IGNORE INTO PackageType (PackageName, PackageDescription, Amentities, BaseCost) VALUES ("Deluxe King Suite", "TV, Free Wifi, Window View", "Pool, Breakfast",155);
    INSERT IGNORE INTO PackageType (PackageName, PackageDescription, Amentities, BaseCost) VALUES ("Double King Suite", "TV, Free Wifi, Window View, Jetted Tub, Kitchenate Area", "Pool, Hot Tub (Unlimited Use), Breakfast, Fitness Center (Unlimited Use)",250);
    Set @PackageTypeID = LAST_INSERT_ID();
     
	INSERT IGNORE INTO Package (PackageTypeID, AddOnID , AddOnDays, TotalCost) VALUES (@PackageTypeID, @AddOnID, 4, 260);
    Set @PackageID = LAST_INSERT_ID();
    
    INSERT IGNORE INTO Reservation (CustomerID, PackageID, NumberOfGuests, CheckInDate, CheckOutDate) VALUES (@CustomerID, @PackageID, 4, "10/27/2019", "11/04/2019");
	
    INSERT IGNORE INTO RewardBenefits (BenefitName, BenefitDescription, RequiredRewards) VALUES ("Free Stay", "1 free day at hotel", 300);
 
-- START Stored Procedures Section-----------------------------
DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `CancelReservation`(
IN customer_id int,
IN reservation_id int)
BEGIN
	SELECT @PackageID FROM Reservation WHERE CustomerID = customer_id and ReservationID = reservation_id;

	DELETE FROM Reservation WHERE CustomerID = customer_id and ReservationID = reservation_id;
	DELETE FROM Package WHERE PackageID = @PackageID;
END$$
DELIMITER ;


DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `GetAddons`()
BEGIN
SELECT 
	AddOnID,
    AmenityName,
    AmenityDescription,
    BaseCost
FROM Addon;
END$$
DELIMITER ;

DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `GetCustomerData`(
IN user_name varchar(8),
IN pass varchar(6))
BEGIN
SELECT 
	CustomerID,
    FirstName,
    LastName,
    UserName,
    Password,
    PhoneNumber,
    EmailAddress,
    RewardsPoints
FROM Customer 
Where UserName = user_name AND Password = pass;
END$$
DELIMITER ;

DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `GetEmployeeData`(
IN user_id int,
IN pass varchar(6))
BEGIN
SELECT 
	EmployeeID,
    FirstName,
    LastName,
    UserID,
    Password
FROM Employee
	WHERE UserID = user_id and Password = pass;
END$$
DELIMITER ;

DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `GetPackageTypes`()
BEGIN
SELECT 
	PackageTypeID,	
	PackageName,		
	PackageDescription,	
	Amentities,			
	BaseCost
FROM PackageType;

END$$
DELIMITER ;

DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `GetReservations`(
IN customer_id int)
BEGIN
SELECT 
	r.ReservationID , 
    p.PackageID, 
    pt.PackageTypeID, 
    pt.BaseCost,
    c.FirstName, 
    c.LastName, 
    r.NumberOfGuests, 
    pt.PackageName, 
    pt.PackageDescription,
    ad.AmenityName, 
    p.AddOnDays, 
    p.TotalCost,
    r.CheckInDate, 
    r.CheckOutDate
FROM Reservation r 
	JOIN Customer c on r.customerId = c.customerid
	JOIN Package p on r.PackageId = p.PackageId
    JOIN PackageType pt on pt.PackageTypeID = p.PackageTypeID
    Left join Addon ad on ad.AddOnID = p.AddOnID
WHERE c.CustomerID = customer_id;
END$$
DELIMITER ;


DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `SaveCustomerData`(
IN first_name varchar(100),
IN last_name varchar(100),
IN user_name varchar(8),
IN pass varchar(6),
IN phoneNumber varchar(13),
IN email_address varchar(1000))
BEGIN
  INSERT INTO Customer (FirstName, LastName, UserName, Password, PhoneNumber, EmailAddress) 
					   VALUES (first_name, last_name, user_name, pass, phoneNumber, email_address);
   
END$$
DELIMITER ;

DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `SaveEmployeeData`(
IN first_name varchar(100),
IN last_name varchar(100),
IN user_id int(4),
IN pass varchar(6))
BEGIN
INSERT INTO Employee (FirstName, LastName, UserID, Password) 
					 VALUES ( first_name, last_name, user_id, pass);
    
END$$
DELIMITER ;


DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `SaveReservation`(
IN customer_id int,
IN num_guests int,
IN check_in_date varchar(10),
IN check_out_date varchar(10),
IN package_type_id int,
IN add_on_id int,
IN add_on_days int,
IN total_cost int)
BEGIN
	INSERT IGNORE INTO Package (PackageTypeID, AddOnID , AddOnDays, TotalCost) 
						VALUES (package_type_id, add_on_id, add_on_days, total_cost);
    Set @PackageID = LAST_INSERT_ID();
    
    INSERT IGNORE INTO Reservation (CustomerID, PackageID, NumberOfGuests, CheckInDate, CheckOutDate) 
							VALUES (customer_id, @PackageID, num_guests, check_in_date, check_out_date);

END$$
DELIMITER ;

DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `GetEligibleBenefits`()
BEGIN
SELECT
	BenefitID,
    BenefitName,
    BeneFitDescription,
    RequiredRewards
FROM RewardBenefits;
END$$
DELIMITER ;





