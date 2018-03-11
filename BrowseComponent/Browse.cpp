//////////////////////////////////////////////////////////////////////////////////////////////////
// Browse.cpp -  support browsing of one or more packages by displaying package descriptions	//
// ver 1.0																						//
//                                                                                 				//
// Environment : C++ Console Application														//
// Platform    : Windows 10 Home x64, Lenovo IdeaPad 700, Visual Studio 2017					//
// Application :  NoSqlDb Key/Value database prototype for CSE687-OOD, Spring 2018				//  
// Author: Theerut Foongkiatcharoen, EECS Department, Syracuse University						//
//         tfoongki@syr.edu																		//
//////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* The package provides a function and helper functions that demonstrate each of the requirements met.
*	- putLine									: reduce the number of characters to type
*	- testBrowse								: demonstrate Requirement #3e, #3f, and #5
*   - createExecutiveElement					: A helper function that helps testBrowse function to create an Executive DbElement
*   - createQueryElement						: A helper function that helps testBrowse function to create a Query DbElement
*   - addDependencies							: A helper function that helps testBrowse function to add dependencies to Executive.cpp

* Required Files:
* ---------------
* Browse.h, Browse.cpp
* DbCore.h, DbCore.cpp
* PayLoad.h, PayLoad.cpp
* StringUtilities.h, StringUtilities.cpp
* TestUtilities.h, TestUtilities.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 March 2018
*/

#include "Browse.h"
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include "../Payload/PayLoad.h"

using namespace NoSqlDb;
using namespace FileSystem;

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

//----< add dependencies to Executive.cpp >----------------------

void addDependencies()
{
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	FileName file1 = "Executive.cpp.1";
	FileName file2 = "Queries.cpp.1";
	std::cout << "\nAdding dependencies to the file: " << file1 << "\n";
	std::cout << "===============================================\n";
	std::cout << "\nAdding " << file2 << " to the file: " << file1 << "\n";
	db[file1].children().push_back(file2);
	dbp.db() = db;
	putLine(2);
	showDb(db);
	putLine(2);
}

//----< creates a Query DbElement >----------------------

DbElement<PayLoad> createQueryElement(bool opened, bool closed, const std::string& desc)
{
	FileName file2 = "Queries.cpp.1";
	DbElement<PayLoad> demoElem;
	demoElem.name(file2);
	demoElem.descrip(desc);
	demoElem.dateTime(DateTime().now());
	PayLoad pl;
	pl.isOpen(opened);
	pl.isClosed(closed);
	pl.filePath(file2);
	pl.categories().push_back("NoSqlDb");
	demoElem.payLoad(pl);
	return demoElem;
}

//----< creates an Executive DbElement >----------------------

DbElement<PayLoad> createExecutiveElement(bool opened, bool closed, const std::string& desc)
{
	FileName file1 = "Executive.cpp.1";
	DbElement<PayLoad> demoElem;
	demoElem.name(file1);
	demoElem.descrip(desc);
	demoElem.dateTime(DateTime().now());
	PayLoad pl;
	pl.isOpen(opened);
	pl.isClosed(closed);
	pl.filePath(file1);
	pl.categories().push_back("NoSqlDb");
	demoElem.payLoad(pl);
	return demoElem;
}


bool testBrowse()
{
	std::cout << "\nSupport browsing of one or more packages by displaying package descriptions.\n";
	std::cout << "\nThe packages to be browsed are identified by a query on the NoSql database that holds metadata for all packages in the repository.\n";
	// create database to hold std::string payload
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	FileName file1 = "Executive.cpp.1";
	FileName file2 = "Queries.cpp.1";

	// create some demo elements and insert into db
	bool open = false;
	bool closed = true;
	db[file1] = createExecutiveElement(open, closed, "browsing Executive");
	db[file2] = createQueryElement(open, closed, "browsing Query");
	dbp.db() = db;
	addDependencies();
	db = dbp.db();
	showDb(db);
	putLine();
	Browse<PayLoad> browse;
	Key key = "Executive.cpp.1";
	FileName fileSearch = "Executive";
	browse.doBrowse(db[key], key, fileSearch);
	return true;

}
#ifdef TEST_BROWSE
int main()
{
	Utilities::Title("Demonstrating Browsing - Requirement #3e, #3f, and #5");
	putLine();

	TestExecutive ex;

	// define test structures with test function and message

	TestExecutive::TestStr ts1{ testBrowse, "Browsing testing" };


	// register test structures with TestExecutive instance, ex

	ex.registerTest(ts1);
	//ex.registerTest(ts2);
	//ex.registerTest(ts3a);
	//ex.registerTest(ts3b);
	//ex.registerTest(ts4b);
	//ex.registerTest(ts5a);
	//ex.registerTest(ts5b);
	//ex.registerTest(ts5c);

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
