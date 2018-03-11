#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version.h - manages version numbering for all files held in the Repository.										//
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
* IVersion.h, VersionDefinitions.h, Version.h, Version.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 28 Feb 2018
*/

#include "VersionDefinitions.h"
#include "IVersion.h"
#include <string>

namespace NoSqlDb
{
	class Version : IVersion
	{
	public:
		Version();
		bool contain(const Key& key);
		VerNum getVersion(const FileName& fileName);
		void restoreVersionsFromFiles();
		bool hasVersion(const FileName& fileName);
		FileName removeVersion(const FileName& fileName);
		FileName addVersion(const FileName& fileName);
		int getLatestVersion(FileName& fileName);
		~Version(){}

	private:
		CurrentVersion currentVersion_;

		
	};
}
