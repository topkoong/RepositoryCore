#pragma once
/////////////////////////////////////////////////////////////////////////////////////
// Checkin.h - manages adding new packages to Repository						   //
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
* This package contains a class Checkin with public functions:
* - doCheckin				: copies file from staging, and saves file to storage
* - checkDependencies		: checks if check-in files have dependencies or not

* Required Files:
* ---------------
* CheckinDefinitions.h, Checkin.h, Checkin.cpp
* DbCore.h, DbCore.cpp
* FileSystem.h, FileSystem.cpp
* Storage.h, Storage.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 2 March 2018
*/
#include "CheckinDefinitions.h"
#include "../DbCore/DbCore.h"
#include "../VersionComponent/Version.h"
#include "../StorageComponent/Storage.h"
#include "../FileSystem/FileSystem.h"

using namespace FileSystem;
namespace NoSqlDb
{
	template<typename T>
	class Checkin
	{
	public:
		Checkin(DbCore<T>& db) : db_(db) {}
		bool doCheckin(const DbElement<T>& el, FileName& fileName);
		bool checkDependencies(const DbElement<T>& el);
		DbCore<T>& db() { return db_; }
	private:
		DbCore<T>& db_;
	};

	//----< copies file from staging, and saves file to storage >----------------------

	template<typename T>
	bool Checkin<T>::checkDependencies(const DbElement<T>& el)
	{
		//DbCore<T> db;
		Storage storage;
		Version v;
		DbElement<PayLoad>::Children dependencies = el.children();
		if (dependencies.empty())
		{
			std::cout << "\nThere're no dependecies\n";
			return true;
		}
		for (FileName dep : dependencies)
		{
			FileName file = v.removeVersion(dep);
			std::vector<FileName> files = Directory::getFiles(storage.stagingPath(), file);
			if (files.empty())
			{
				std::cout << "\n" << dep << "is not present in the Repository\n";
				return false;
			}
			PayLoad childPlayLoad = db_[file].payLoad();
			if (childPlayLoad.isOpen())
			{
				std::cout << "\n" << "****Cannot check in " << el.name() << " because " << dep << " is still open.****\n";
				return false;
			}
		}
		return true;
	}

	//----< copies file from staging, and saves file to storage >----------------------

	template<typename T>
	bool Checkin<T>::doCheckin(const DbElement<T>& el, FileName& fileName)
	{
		std::cout << "\nSupport check-in by accepting: " << fileName << "\n";
		//DbProvider dbp;
		//DbCore<PayLoad> db = dbp.db();
		//DbCore<T> db;
		/*db[fileName] = el;*/
		db_[fileName] = el;
		Version v;
		Storage storage;
		if (!checkDependencies(el))
			return false;
		// should we create new version or modify old version
		VerNum fileVer = v.getLatestVersion(fileName);
		bool doModify, t1;
		if (db_.contains(fileName))
		{
			/*PayLoad pl = db[fileName].payLoad();*/
			PayLoad pl = db_[fileName].payLoad();
			if (fileVer == 0) // no previous checkin so make new version
			{
				doModify = false;
			}
			else if (pl.isClosed()) // last checkin was closed so make new version
			{
				doModify = false;
			}
			else // last checkin was open so just modify existing version
			{
				doModify = true;
			}
			// copy source file to versioned file in Storage
			if (doModify)
				t1 = storage.modifyFile(fileName);
			else
				t1 = storage.addFile(fileName);
		}
		else
			t1 = storage.addFile(fileName);
		// get version from version cache, possibly updated by addFile
		v.restoreVersionsFromFiles();
		fileVer = v.getLatestVersion(fileName);
		// build versioned fileSpec and add to MetaData instance
		FileSpec buildVersionedFile = fileName + "." + std::to_string(fileVer);
		if (!t1)
			return false;
		db_[buildVersionedFile] = el;
		//dbp.db() = db;
		return true;
	}
}