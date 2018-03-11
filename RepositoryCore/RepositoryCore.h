#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RepositoryCore.h - provides means to check-in, version, browse, and check-out source code packages.  			//
// ver 1.0																											//
//																													//
// Environment : C++ Console Application																			//
// Platform    : Windows 10 Home x64, Lenovo IdeaPad 700, Visual Studio 2017										//
// Application :  NoSqlDb Key/Value database prototype for CSE687-OOD, Spring 2018									//  
// Author: Theerut Foongkiatcharoen, EECS Department, Syracuse University											//
//         tfoongki@syr.edu																							//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
** This package contains a class RepositoryCore with public methods:
* - checkin			: copies file from staging, and saves file to storage
* - checkout		: copy all the package metadata and referred files from a dependency tree to the file Staging area
* - browse			: support browsing of one or more packages by displaying package descriptions
* 
* The package provides a function and helper functions that demonstrate each of the requirements met.
*	- putLine									: reduce the number of characters to type
*	- testDoCheckout							: demonstrate requirement #2d
*   - createExecutiveElement					: A helper function that helps testDoCheckout function to create an Executive DbElement
*   - createQueryElement						: A helper function that helps testDoCheckout function to create a Query DbElement
*   - addDependencies							: A helper function that helps testDoCheckout function to add dependencies to Executive.cpp

* Required Files:
* ---------------
* RepositoryCore.h, RepositoryCore.cpp
* StringUtilities.h, StringUtilities.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 March 2018
*/

#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../DbCore/DbCore.h"
#include "../Payload/PayLoad.h"
namespace NoSqlDb
{
	class RepositoryCore
	{
	public:
		RepositoryCore() { std::cout << "\n\nRepositoryCore has been created to demonstrate Requirement #6\n\n"; }
		void checkin();
		void checkout();
		void browse();
		~RepositoryCore() { std::cout << "\n\nRepositoryCore has been destroyed\n\n"; }
	};

	//class DbProvider
	//{
	//public:
	//	 DbCore<PayLoad>& db() { return db_; }
	//private:
	//	static DbCore<PayLoad> db_;
	//};
	
}