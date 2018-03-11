/////////////////////////////////////////////////////////////////////////////////////
// Checkout.h - supports extraction of package dependency graphs  				   //
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
* The package provides a function and helper functions that demonstrate each of the requirements met.
*	- putLine									: reduce the number of characters to type
*	- testDoCheckout							: demonstrate Requirement #3d and #3e
*   - createExecutiveElement					: A helper function that helps testDoCheckout function to create an Executive DbElement
*   - createQueryElement						: A helper function that helps testDoCheckout function to create a Query DbElement
*   - addDependencies							: A helper function that helps testDoCheckout function to add dependencies to Executive.cpp

* Required Files:
* ---------------
* Checkout.h, Checkout.cpp
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

#include "Checkout.h"
#include "../Payload/PayLoad.h"
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
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

//template <typename T>
//bool Checkout<PayLoad>::doCheckout(const DbElement<T>& el, FileName& fileName)
//{
//	retrieveDependencies(el, fileName);
//	if (fileDependencies().size() == 0)
//	{
//		std::cout << "Dependencies are not present in the RepoStorage \n";
//		return true;
//	}
//	else
//	{
//		for (FileName dfile : fileDependencies())
//			std::cout << "File Dependencies: " << dfile << "\n";
//		return true;
//	}
//}

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

//----< demonstrate requirement #2d >----------------------

bool testDoCheckout()
{
	// create database to hold std::string payload
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	FileName file1 = "Executive.cpp.1";
	FileName file2 = "Queries.cpp.1";
	bool open = false;
	bool closed = true;
	// create some demo elements and insert into db
	db[file1] = createExecutiveElement(open, closed, "checking out Executive");
	db[file2] = createQueryElement(open, closed, "checking out Query");
	dbp.db() = db;
	// add dependencies to Executive.cpp
	addDependencies();
	db = dbp.db();
	FileName checkoutFile = file1;
	Checkout<PayLoad> ck;
	Utilities::title("Checking out " + checkoutFile);
	ck.doCheckout(db[file1], checkoutFile);
	return true;
}


#ifdef TEST_CHECKOUT
int main()
{
	Utilities::Title("Demonstrating Checkout - Requirement #3d and #3e");
	putLine();

	TestExecutive ex;

	// define test structures with test function and message

	TestExecutive::TestStr ts1{ testDoCheckout, "Checkout testing" };


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