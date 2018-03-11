/////////////////////////////////////////////////////////////////////////////////////
// Checkin.cpp - manages adding new packages to Repository						   //
// ver 1.0                                                                         //
//                                                                                 //
// Environment : C++ Console Application                                           //
// Platform    : Windows 10 Home x64, Lenovo IdeaPad 700, Visual Studio 2017       //
// Application :  NoSqlDb Key/Value database prototype for CSE687-OOD, Spring 2018 //  
// Author: Theerut Foongkiatcharoen, EECS Department, Syracuse University          //
//         tfoongki@syr.edu                                                        //
/////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* The package provides a function and function helpers that demonstrate each of the requirements met.
*	- putLine									: reduce the number of characters to type
*	- testDoCheckin								: demonstrate Requirement #3c, #3e, and #4
*   - createExecutiveElement					: creates an Executive DbElement
*   - createPersistElement						: creates a Persist DbElement
*   - createQueryElement						: creates a Query DbElement
*   - addDependencies							: add dependencies to Executive.cpp
*   - closeCheckinWithOpenedDependencies		: A helper function that helps testDoCheckin function to close Executive.cpp file.
*   - closeDependencies							: A helper function that helps testDoCheckin function to close Queries.cpp file and Persist.cpp file.
*   - checkinExecutiveFile						: A helper function that helps testDoCheckin function to check in Executive.cpp file.
*   - checkinQueriesFile						: A helper function that helps testDoCheckin function to check in Queries.cpp file.
*   - checkinPersistFile						: A helper function that helps testDoCheckin function to check in Persist.cpp file.

* Required Files:
* ---------------
* Checkin.h, Checkin.cpp
* DbCore.h, DbCore.cpp
* PayLoad.h, PayLoad.cpp
* FileSystem.h, FileSystem.cpp
* StringUtilities.h, StringUtilities.cpp
* TestUtilities.h, TestUtilities.cpp

*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 2 March 2018
*/
#include "Checkin.h"
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include "../Payload/PayLoad.h"



using namespace NoSqlDb;
//using namespace FileSystem;

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
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

//----< creates an Executive DbElement >----------------------

DbElement<PayLoad> createExecutiveElement(bool opened, bool closed, const std::string& desc)
{
	DbElement<PayLoad> demoElem;
	demoElem.name("Executive package");
	demoElem.descrip(desc);
	demoElem.dateTime(DateTime().now());
	PayLoad pl;
	pl.isOpen(opened);
	pl.isClosed(closed);
	FileName file1 = "Executive.cpp";
	pl.filePath(file1);
	pl.categories().push_back("NoSqlDb");
	demoElem.payLoad(pl);
	return demoElem;
}

//----< creates a Query DbElement >----------------------

DbElement<PayLoad> createQueryElement(bool opened, bool closed, const std::string& desc)
{
	DbElement<PayLoad> demoElem;
	demoElem.name("Queries package");
	demoElem.descrip(desc);
	demoElem.dateTime(DateTime().now());
	PayLoad pl;
	pl.isOpen(opened);
	pl.isClosed(closed);
	FileName file2 = "Queries.cpp";
	pl.filePath(file2);
	pl.categories().push_back("NoSqlDb");
	demoElem.payLoad(pl);
	return demoElem;
}

//----< creates a Persist DbElement >----------------------

DbElement<PayLoad> createPersistElement(bool opened, bool closed, const std::string& desc)
{
	DbElement<PayLoad> demoElem;
	demoElem.name("Persist package");
	demoElem.descrip(desc);
	demoElem.dateTime(DateTime().now());
	PayLoad pl;
	pl.isOpen(opened);
	pl.isClosed(closed);
	FileName file3 = "Persist.cpp";
	pl.filePath(file3);
	pl.categories().push_back("NoSqlDb");
	demoElem.payLoad(pl);
	return demoElem;
}

//----< add dependencies to Executive.cpp >----------------------

void addDependencies()
{
	DbProvider dbp;
	Checkin<PayLoad> ck(dbp.db());

	FileName file1 = "Executive.cpp";
	FileName file2 = "Queries.cpp";
	FileName file3 = "Persist.cpp";
	std::cout << "\nAdding dependencies to the file: " << file1 << "\n";
	std::cout << "===============================================\n";
	std::cout << "\nAdding " << file2 << " to the file: " << file1 << "\n";
	ck.db()[file1].children().push_back(file2);

	showDb(ck.db());
	putLine(2);
	std::cout << "\nAdding " << file3 << " to the file: " << file1 << "\n";
	ck.db()[file1].children().push_back(file3);
	dbp.db() = ck.db();
	showDb(ck.db());
	putLine(2);
}

//----< A helper function that helps testDoCheckin function to close Executive.cpp file. >----------------------

void closeCheckinWithOpenedDependencies()
{
	//DbProvider dbp;
	//DbCore<PayLoad> db = dbp.db();
	DbProvider dbp;
	Checkin<PayLoad> ck(dbp.db());
	FileName file1 = "Executive.cpp";
	FileName file2 = "Queries.cpp";
	FileName file3 = "Persist.cpp";
	std::cout << "Attempting to close " << file1 << " while " << file2 << " and " << file3 << " are in the open status.\n";
	std::cout << "===============================================\n";
	putLine();
	//Checkin<PayLoad> ck;
	if (ck.doCheckin(ck.db()[file1], file1))
	{
		ck.db()[file1].payLoad().isClosed(true);
		ck.db()[file1].payLoad().isOpen(false);
		ck.db()[file1].descrip("Attempting to close " + file1);
		/*dbp.db() = db;*/
		dbp.db() = ck.db();
	}
	ck.db()[file1].payLoad().showDb(ck.db());
	putLine(2);
	dbp.db() = ck.db();
}

//----< A helper function that helps testDoCheckin function to close Queries.cpp file and Persist.cpp file. >----------------------

void closeDependencies()
{
	//DbProvider dbp;
	//DbCore<PayLoad> db = dbp.db();
	DbProvider dbp;
	Checkin<PayLoad> ck(dbp.db());
	FileName file2 = "Queries.cpp";
	FileName file3 = "Persist.cpp";
	std::cout << "Attempting to close " << file2 << "\n";
	std::cout << "===============================================\n";
	/*Checkin<PayLoad> ck;*/
	if (ck.doCheckin(ck.db()[file2], file2))
	{
		ck.db()[file2].payLoad().isClosed(true);
		ck.db()[file2].payLoad().isOpen(false);
		ck.db()[file2].descrip("Attempting to close " + file2);
		/*dbp.db() = db;*/
		dbp.db() = ck.db();
	}
	ck.db()[file2].payLoad().showDb(ck.db());
	putLine(2);
	/*dbp.db() = db;*/
	dbp.db() = ck.db();
	std::cout << "Attempting to close " << file3 << "\n";
	std::cout << "===============================================\n";
	if (ck.doCheckin(ck.db()[file3], file3))
	{
		ck.db()[file3].payLoad().isClosed(true);
		ck.db()[file3].payLoad().isOpen(false);
		ck.db()[file3].descrip("Attempting to close " + file3);
		/*dbp.db() = db;*/
		dbp.db() = ck.db();
	}
	ck.db()[file3].payLoad().showDb(ck.db());
	putLine();
	/*dbp.db() = db;*/
	dbp.db() = ck.db();
}

//----< A helper function that helps testDoCheckin function to check in Executive.cpp file. >----------------------

void checkinExecutiveFile(bool open, bool closed, const std::string& desc)
{
	//DbProvider dbp;
	//DbCore<PayLoad> db = dbp.db();
	DbProvider dbp;
	Checkin<PayLoad> ck(dbp.db());
	FileName file1 = "Executive.cpp";
	FileName file2 = "Queries.cpp";
	FileName file3 = "Persist.cpp";
	ck.db()[file1] = createExecutiveElement(open, closed, desc);
	std::cout << "\n" << desc;
	std::cout << "\n=================================================================================\n";
	//Checkin<PayLoad> ck;
	ck.doCheckin(ck.db()[file1], file1);
	ck.db()[file1].payLoad().showDb(ck.db());
	std::cout << "\n\nShowing all the database elements\n";
	std::cout << "======================================\n";
	dbp.db() = ck.db();
	showDb(ck.db());
}

//----< A helper function that helps testDoCheckin function to check in Queries.cpp file. >----------------------

void checkinQueriesFile(bool open, bool closed, const std::string& desc)
{
	//DbProvider dbp;
	//DbCore<PayLoad> db = dbp.db();
	DbProvider dbp;
	Checkin<PayLoad> ck(dbp.db());
	FileName file2 = "Queries.cpp";

	//Checkin<PayLoad> ck;
	ck.db()[file2] = createQueryElement(open, closed, desc);
	/*dbp.db() = db;*/
	dbp.db() = ck.db();
	putLine(2);
	std::cout << "\n" << desc;
	std::cout << "\n===============================================\n";
	ck.doCheckin(ck.db()[file2], file2);
	ck.db()[file2].payLoad().showDb(ck.db());
	putLine(2);
	std::cout << "\n\nShowing all the database elements";
	std::cout << "\n===============================================\n";
	//dbp.db() = db;
	dbp.db() = ck.db();
	showDb(ck.db());
}

//----< A helper function that helps testDoCheckin function to check in Persist.cpp file. >----------------------

void checkinPersistFile(bool open, bool closed, const std::string& desc)
{
	//DbProvider dbp;
	//DbCore<PayLoad> db = dbp.db();
	DbProvider dbp;
	Checkin<PayLoad> ck(dbp.db());
	FileName file3 = "Persist.cpp";
	/*Checkin<PayLoad> ck;*/
	ck.db()[file3] = createPersistElement(open, closed, desc);
	dbp.db() = ck.db();
	putLine(2);
	std::cout << "\n" << desc;
	std::cout << "\n===============================================\n";
	ck.doCheckin(ck.db()[file3], file3);
	ck.db()[file3].payLoad().showDb(ck.db());
	putLine(2);
	std::cout << "\n\nShowing all the database elements";
	std::cout << "\n===============================================\n";
	dbp.db() = ck.db();
	showDb(ck.db());
	putLine(2);
}

//----< creates a Persist DbElement >----------------------

bool testDoCheckin()
{
	std::cout << "Check-in: provides the functionality to start a new package version by accepting files, appending version numbers to their filenames, providing dependency and category information, creating metadata, and storing the files in a designated location.\n\n";
	std::cout << "Checkin Executive file with closed status\n";
	bool open = false;
	bool closed = true;
	checkinExecutiveFile(open, closed, "first checking in Executive");
	open = true;
	closed = false;
	checkinExecutiveFile(open, closed, "Checkin Executive file again with open status - should increase version number by 1");
	checkinExecutiveFile(open, closed, "A package with open check-in can be modified without altering its version number");
	std::cout << "\nCheckin Queries and Persist files with open status\n";
	checkinQueriesFile(open, closed, "first checking in Query");
	checkinPersistFile(open, closed, "first checking in Persist");
	// add dependencies to Executive.cpp
	addDependencies();
	 //attempt to close Executive.cpp while Queries.cpp and Persist.cpp are still open (failed)
	closeCheckinWithOpenedDependencies();
	//close Queries.cpp (pass)
	//close Persist.cpp (pass)
	closeDependencies();
	open = false;
	closed = true;
	checkinExecutiveFile(open, closed, "Checkin Executive file again with closed status - version of the package becomes immutable");
	return true;
}



#ifdef TEST_CHECKIN
int main()
{
	Utilities::Title("Demonstrating Checkin - Requirement #3c, #3e, and #4");
	putLine();

	TestExecutive ex;

	// define test structures with test function and message

	TestExecutive::TestStr ts1{ testDoCheckin, "Checkin testing" };


	// register test structures with TestExecutive instance, ex

	ex.registerTest(ts1);

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