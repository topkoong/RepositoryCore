#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version.cpp - manages version numbering for all files held in the Repository.									//
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
* This package contains a class Version with public methods:
* - contain						: Does the current version have the specified version?
* - addVersion					: adds version text to filename
* - removeVersion				: removes version text from filename
* - hasversion					: filename has version number?
* - getVersion					: returns version number of specified fileName
* - restoreVersionsFromFile		: creates an unordered map of version numbers
* - getLatestVersion			: returns highest version number of all files with given category and name
* 
* Required Files:
* ---------------
* Version.h, Version.cpp
* StringUtilities.h, StringUtilities.cpp
* FileSystem.h, FileSystem.cpp
* Storage.h, Storage.cpp
* 
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 28 Feb 2018
*/
#include "Version.h"
#include "../FileSystem/FileSystem.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../StorageComponent/Storage.h"


using namespace NoSqlDb;
using namespace FileSystem;

/*----< constructor >------------------------------------------*/
/*
* Builds latest version number map
*/

Version::Version()
{
	std::cout << "\n\n Version has been created to demonstrate Requirement #3e\n\n";
	restoreVersionsFromFiles();
}

/*----< Does the current version have the specified version? >-------*/

bool Version::contain(const Key& key)
{
	iterator iter = currentVersion_.find(key);
	return iter != currentVersion_.end();
}

/*----< extract version number from specified fileName >-------*/
/*
*  Not necessarily the latest version number.
*  Returns zero if file has no version number.
*/

int Version::getVersion(const FileName& fileName)
{
	VerNum ver = 0;
	int pos = fileName.find_last_of(".");
	std::string verStr = fileName.substr(pos + 1);
	try
	{
		ver = std::stoi(verStr);
		return ver;
	}
	catch (const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
		return 0;
	}
}

/*----< creates an unordered map of version numbers >----------------*/
/*
*  Reads filenames from each Storage category and builds
*  Key value pair with filenames and largest version number values.
*  
*/

void Version::restoreVersionsFromFiles()
{
	Storage storage;
	std::vector<std::string> files = Directory::getFiles(storage.storagePath(), "*");
	if (files.size() != 0)
	{
		for (std::string file : files)
		{
			FileName fileName = file;
			FileName file_nv = removeVersion(file);
			Key key = file_nv;
			VerNum versionNum = getVersion(file);
			if (contain(key))
			{
				if (versionNum > currentVersion_[key])
					currentVersion_[key] = versionNum;
			}
			else
				currentVersion_[key] = versionNum;
		}
	}
}

/*----< does this fileName have a version number? >------------*/

bool Version::hasVersion(const FileName& fileName)
{
	int pos = fileName.find_last_of('.');
	std::string end = fileName.substr(pos + 1);
	try
	{
		std::stoi(end);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
		return false;
	}
}

/*----< strips version number from filename >------------------*/
/*
* Used when retrieving file from storage.
*/

FileName Version::removeVersion(const FileName& fileName)
{
	int pos = fileName.find_last_of('.');
	std::string end = fileName.substr(pos + 1);
	try
	{
		std::stoi(end);
		return fileName.substr(0, pos);
	}
	catch (const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
		return fileName;
	}
}

/*----< adds version number to filename >----------------------*/
/*
* Adds version number equal to 1 + latestVersionNumber.
* Used before storing file in Storage.
*/

FileName Version::addVersion(const FileName& fileName)
{
	Key key = removeVersion(fileName);
	VerNum versionNumber = 0;
	if (contain(key))
		versionNumber = currentVersion_[key];
	currentVersion_[key] = ++versionNumber;
	return fileName + "." + std::to_string(versionNumber);
}

/*----< returns the current version number for filename >------*/

int Version::getLatestVersion(FileName& fileName)
{
	int temp = 0;
	fileName = removeVersion(fileName);
	Key key = fileName;
	if (contain(key))
		temp = currentVersion_[key];
	return temp;
}


bool testVersion()
{
	Version v;
	v.restoreVersionsFromFiles();
	return true;
}



#ifdef TEST_VERSION
int main()
{	

	Utilities::Title("Demonstrating Version - Requirement #3e");
	putLine();

	TestExecutive ex;

	// define test structures with test function and message

	TestExecutive::TestStr ts1{ testVersion, "Version testing" };


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
