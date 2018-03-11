#pragma once
//////////////////////////////////////////////////////////////////////////////////////
// Executive.cpp - demonstrate Project2 requirements 								//
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
* This package defines class DbProviderExe that provides mechanism
* to share a test database between test functions without explicitly passing as a function argument.
* The package also provides functions that demonstrates each of the requirements met.
* 
* - testR1								: demonstrate requirement #1
* - testR2								: demonstrate requirement #2
* - testR								: demonstrate requirement #3 - #7
* 
* Required Files:
* ---------------
* Executive.h, Executive.cpp,
* TestUtilities.h, TestUtilities.cpp.
* Checkin.h, Checkin.cpp,
* Browse.h, Browse.cpp,
* FileSystem.h, FileSystem.cpp
* 
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 Feb 2018
*/


#include "Executive.h"
#include "../CheckinComponent/Checkin.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <iostream>
#include "../Payload/PayLoad.h"
//#include "../FileSystem/FileSystem.h"

using namespace Utilities;
using namespace NoSqlDb;

///////////////////////////////////////////////////////////////////////
// DbProvider class
// - provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument.

class DbProviderExe
{
public:
	DbCore<PayLoad>& db() { return db_; }
private:
	static DbCore<PayLoad> db_;
};
DbCore<PayLoad> DbProviderExe::db_;

//----< demonstrate requirement #1 >------------------------------------------

bool testR1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.\n\n";
	return true; // would not compile unless C++11
}

//----< demonstrate requirement #2 >------------------------------------------

bool testR2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete for all heap-based memory management.\n\n";
	return true;
}

//----< demonstrate project#2 requirement #3 - #7 >----------------------------

bool testProject2()
{
	Executive exe;
	DbProviderExe dbp;
	DbCore<PayLoad> db = dbp.db();
	Utilities::Title("Demonstrating Checkin - Requirement #3c, #3e, and #4");
	exe.repo().checkin();
	db = dbp.db();

	Utilities::Title("Demonstrating Checkout - Requirement #3d and #3e");
	exe.repo().checkout();
	db = dbp.db();
	Utilities::Title("Demonstrating Browsing - Requirement #3e, #3f, and #5");
	exe.repo().browse();
	db = dbp.db();
	return true;
}

int main()
{
	Utilities::Title("The TestExecutive shall execute a series of tests that clearly demonstrate your project satisfies each of the Requirements, #1 - #7");
	//putLine();
	TestExecutive ex;
	// define test structures with test function and message
	TestExecutive::TestStr ts1{ testR1, "Use C++11" };
	TestExecutive::TestStr ts2{ testR2, "Use streams and new and delete" };
	TestExecutive::TestStr ts3{ testProject2, "Testing Project2 to meet all requirements" };
	// register test structures with TestExecutive instance, ex
	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3);
	// run tests
	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n\n  all tests passed";
	else
		std::cout << "\n\n  at least one test failed";

	//putLine(5);
	return 0;
}

