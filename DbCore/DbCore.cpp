/////////////////////////////////////////////////////////////////////////////////////
// DbCore.cpp - Implements NoSql database prototype								   //
// ver 1.0                                                                         //
//                                                                                 //
// Environment : C++ Console Application                                           //
// Platform    : Windows 10 Home x64, Lenovo IdeaPad 700, Visual Studio 2017       //
// Application :  NoSqlDb Key/Value database prototype for CSE687-OOD, Spring 2018 //  
// Author: Theerut Foongkiatcharoen, EECS Department, Syracuse University          //
//         tfoongki@syr.edu                                                        //
// Source: Dr. Jim Fawcett, EECS Department, CST 4-187, Syracuse University        //
//         jfawcett @twcny.rr.com                                                  //
/////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package defines class DbProvider that provides mechanism
* to share a test database between test functions without explicitly passing as a function argument.
*
* The package also provides functions that demonstrates each of the requirements met.
*   ----------------------------------------------------------
*   - putLine								: reduce the number of characters to type
*   - testR1								: demonstrate requirement #1
*   - testR2								: demonstrate requirement #2
*   - testR3a								: demonstrate firsst part of requirement #3
*   - testR3b								: demonstrate second part of requirement #3 and first part of requirement #4
*   - testR4b								: demonstrate second part of requirement #4
*   - testR5a								: demonstrate first part of requirement #5
*   - testR5b								: demonstrate second part of requirement #5
*   - testR5c								: demonstrate third part of requirement #5

* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* DateTime.h, DateTime.cpp
* StringUtilities.h, StringUtilities.cpp
* TestUtilities.h, TestUtilities.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 Feb 2018
*/

#include "DbCore.h"
#include "../Payload/PayLoad.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <iostream>
#include <functional>

using namespace NoSqlDb;

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n=1, std::ostream& out = std::cout)
{
  Utilities::putline(n, out);
};

///////////////////////////////////////////////////////////////////////
// DbProvider class
// - provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument.

class DbProvider
{
public:
	DbCore<PayLoad>& db() { return db_; }
private:
	static DbCore<PayLoad> db_;
};
DbCore<PayLoad> DbProvider::db_;



///////////////////////////////////////////////////////////////////////
// test functions

//----< demo requirement #1 >------------------------------------------

bool testR1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.";
	putLine();
	return true; // would not compile unless C++11
}

//----< demo requirement #2 >------------------------------------------

bool testR2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	putLine();
	return true;
}

//----< demonstrate first part of requirement #3 >----------------------------

bool testR3a()
{
	Utilities::title("Demonstrating Requirement #3a - creating DbElement");
	std::cout << "\n\n  Creating a db element with key \"Fawcett\":\n";
	// create database to hold std::string payload
	DbCore<PayLoad> db;
	DbProvider dbp;
	dbp.db() = db;
	// check whether db contains this key already?
	if (db.contains("Fawcett"))
	{
		std::cout << "\n  we cannot insert the key named " << "Fawcett" << " to the db\n";
		return false;
	}
	// create some demo elements and insert into db
	DbElement<PayLoad> demoElem;
	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	PayLoad pL;
	pL.filePath("C:/InsertDataDemo.txt");
	pL.categories().push_back("Instructor");
	demoElem.payLoad(pL);
	if (demoElem.name() != "Jim")
		return false;
	if (demoElem.descrip() != "Instructor for CSE687")
		return false;
	if (demoElem.dateTime().now() != DateTime().now())
		return false;
	if (demoElem.payLoad().filePath() != "C:/InsertDataDemo.txt")
		return false;
	if (!(std::find(demoElem.payLoad().categories().begin(), demoElem.payLoad().categories().end(), "Instructor") != demoElem.payLoad().categories().end()))
		return false;
	showHeader();
	showElem(demoElem);
	db["Fawcett"] = demoElem;
	dbp.db() = db;
	putLine();
	return true;
}

//----< demonstrate second part of requirement #3 and first part of requirement #4>----------------------------

bool testR3b()
{
	Utilities::title("Demonstrating Requirement #3b&4a - creating DbCore and adding element with key");
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	DbElement<PayLoad> demoElem = db["Fawcett"];
	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	PayLoad pL;
	pL.filePath("C:/AdditionKVDemo.txt");
	pL.categories().push_back("TA");
	demoElem.payLoad(pL);
	db["Salman"] = demoElem;
	demoElem.name("Jianan");
	PayLoad pL2; 
	pL2.filePath("C:/AdditionKVDemo2.txt"); pL2.categories().push_back("TA"); demoElem.payLoad(pL2);
	db["Sun"] = demoElem;
	PayLoad pL3;
	pL3.filePath("C:/AdditionKVDemo3.txt"); pL3.categories().push_back("TA"); demoElem.payLoad(pL3);
	demoElem.name("Nikhil");
	db["Prashar"] = demoElem;
	PayLoad pL4;
	pL4.filePath("C:/AdditionKVDemo4.txt"); pL4.categories().push_back("TA"); demoElem.payLoad(pL4);
	demoElem.name("Pranjul");
	db["Arora"] = demoElem;
	PayLoad pL5;
	pL5.filePath("C:/AdditionKVDemo5.txt"); pL5.categories().push_back("TA"); demoElem.payLoad(pL5);
	demoElem.name("Akash");
	db["Anjanappa"] = demoElem;
	std::cout << "\n\n  after adding elements with keys: \n";
	DbCore<PayLoad>::Keys keys = db.keys();
	showKeys(db);
	std::cout << "\n\n  make all the new elements children of element with key \"Fawcett\"\n";
	db["Fawcett"].children().push_back("Salman");
	db["Fawcett"].children().push_back("Sun");
	db["Fawcett"].children().push_back("Prashar");
	db["Fawcett"].children().push_back("Arora");
	db["Fawcett"].children().push_back("Anjanappa");
	showHeader();
	showElem(db["Fawcett"]);
	db["Salman"].children().push_back("Sun");
	db["Salman"].children().push_back("Prashar");
	db["Salman"].children().push_back("Arora");
	db["Salman"].children().push_back("Anjanappa");
	dbp.db() = db;
	std::cout << "\n\n  showing all the database elements:";
	showDb(db);
	std::cout << "\n\n  database keys are: ";
	showKeys(db);
	return true;
}

//----< demonstrate second part of requirement #4 >----------------------------

bool testR4b() {
	Utilities::title("Demonstrating Requirement #4b - deletion of key/value pairs");
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	if (db.deleteRecord("Sun")) {
		// display the results
		dbp.db() = db;
		putLine();
		std::cout << "\n  showing all the database elements:";
		showDb(db);
		putLine();

		std::cout << "\n  database keys are: ";
		showKeys(db);

		putLine();
		return true;
	}

	std::cout << "\n  we cannot find the key named " << "Sun" << " to the db\n";
	return false;
}

//----< demonstrate first part of requirement #5 >----------------------------

bool testR5a() {
	Utilities::title("Demonstrating Requirement #4a - adding a child element to Fawcett");
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	if (!db.contains("Fawcett"))
	{
		std::cout << "\n  we cannot find the key named " << "Fawcett" << " to the db\n";
		return false;
	}

	DbElement<PayLoad> childDBElement;
	childDBElement.name("Theerut");
	childDBElement.descrip("A grad student");
	PayLoad pL;
	pL.filePath("C:/AddChildDemo.txt");
	pL.categories().push_back("Student");
	childDBElement.payLoad(pL);
	db["Foongkiatcharoen"] = childDBElement;
	if (!db.contains("Foongkiatcharoen"))
		return false;
	std::cout << "\n  after adding an element with key: " << "\"" << "Foongkiatcharoen" << "\"";
	DbCore<PayLoad>::Keys keys = db.keys();
	showKeys(db);
	putLine();
	std::cout << "\n  Adding a new child element to key " << "\"" << "Fawcett" << "\"";
	db.addChild("Fawcett", "Foongkiatcharoen");
	dbp.db() = db;
	putLine();
	showDb(db);
	return true;
}

//----< demonstrate second part of requirement #5 >----------------------------

bool testR5b() {
	Utilities::title("Demonstrating Requirement #5b - deletion of relationship");
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	if (db.deleteChild("Salman", "Nikhil")) {
		// display the results
		dbp.db() = db;
		putLine();
		std::cout << "\n  showing all the database elements:";
		showDb(db);
		putLine();

		std::cout << "\n  database keys are: ";
		showKeys(db);

		putLine();
		return true;
	}

	std::cout << "\n  we cannot find the key named " << "Salman" << " to the db\n";
	return false;
}

//----< demonstrate third part of requirement #5 >----------------------------

bool testR5c() {
	Utilities::title("Demonstrating Requirement #3b - editing text metadata and replacing an existing value's instance with a new instance");
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	if (!db.contains("Fawcett"))
	{
		std::cout << "\n  we cannot find the key named " << "Fawcett" << " to the db\n";
		return false;
	}
	std::cout << "\n\n  Editing an element with key: " << "\"" << "Fawcett" << "\"\n";
	DbElement<PayLoad> dbElement = db["Fawcett"];
	dbElement.descrip("The best prof");
	PayLoad pL;
	pL.filePath("C:/EditMetaDataDemo.txt");
	pL.categories().push_back("EditMetaDataDemo.txt");
	dbElement.payLoad(pL);
	db["Fawcett"] = dbElement;
	// display the results
	dbp.db() = db;
	putLine();
	std::cout << "\n  showing all the database elements:";
	showDb(db);
	putLine();

	std::cout << "\n  database keys are: ";
	showKeys(db);

	putLine();
	return true;
}

#ifdef TEST_DBCORE
using namespace Utilities;
int main()
{
	Utilities::Title("Testing DbCore - He said, she said database");
	putLine();

	TestExecutive ex;

	// define test structures with test function and message

	TestExecutive::TestStr ts1{ testR1, "Use C++11" };
	TestExecutive::TestStr ts2{ testR2, "Use streams and new and delete" };
	TestExecutive::TestStr ts3a{ testR3a, "Creating DbElement" };
	TestExecutive::TestStr ts3b{ testR3b, "Creating DbCore and adding element with key" };
	TestExecutive::TestStr ts4b{ testR4b, "Deletion of key/value pairs" };
	TestExecutive::TestStr ts5a{ testR5a, "Addition of relationships" };
	TestExecutive::TestStr ts5b{ testR5b, "Deletion of relationships" };
	TestExecutive::TestStr ts5c{ testR5c, "Editing text metadata and replacing an existing value's instance with a new instance" };

	// register test structures with TestExecutive instance, ex

	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3a);
	ex.registerTest(ts3b);
	ex.registerTest(ts4b);
	ex.registerTest(ts5a);
	ex.registerTest(ts5b);
	ex.registerTest(ts5c);

	// run tests

	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n\n  all tests passed";
	else
		std::cout << "\n\n  at least one test failed";

	putLine(5);
	return 0;
}
#endif