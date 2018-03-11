#pragma once
/////////////////////////////////////////////////////////////////////////////////////
// Executive.h - demonstrate Project2 requirements 								   //
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
* The package provides functions that demonstrates each of the requirements met.
*   ----------------------------------------------------------
*   - repo								: getter of repo_
*
*
* Required Files:
* ---------------
* Executive.h, Executive.cpp,
* RepositoryCore.h, RepositoryCore.cpp

*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 Feb 2018
*/

#include "../RepositoryCore/RepositoryCore.h"
//#include "../Utilities/StringUtilities/StringUtilities.h"


namespace NoSqlDb
{
	class Executive
	{
	public:
		Executive() { std::cout << "\n\nTestExecutive has been created to demonstrate Requirement #7\n\n"; }
		RepositoryCore& repo() { return repo_; }
		~Executive() { std::cout << "\n\nTestExecutive has been destroyed\n\n"; }

	private:
		RepositoryCore repo_;
	};
}


