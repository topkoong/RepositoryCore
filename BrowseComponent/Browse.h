#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////
// Browse.h -  support browsing of one or more packages by displaying package descriptions  //
// ver 1.0																					//
//                                                                                 			//
// Environment : C++ Console Application													//
// Platform    : Windows 10 Home x64, Lenovo IdeaPad 700, Visual Studio 2017				//
// Application :  NoSqlDb Key/Value database prototype for CSE687-OOD, Spring 2018			//  
// Author: Theerut Foongkiatcharoen, EECS Department, Syracuse University					//
//         tfoongki@syr.edu																	//
//////////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package contains a class Browse with public methods:
* - doBrowse				: supports traversal of package dependency identified by a query on the NoSql database that holds metadata for all packages in the repository.
* - extractFileName			: extract file name from a versioned file
* - retrieveDependencies	: visit names of all packages on a dependency (sub)tree
* - fileDependencies		: getter and setter of _fileDependencies
* - fileList				: getter and setter of _fileList
* - displayFile				: displays package descriptions
* - contain					: check if dependencies contain the particular filename
*
* Required Files:
* ---------------
* BrowseDefinitions.h, Browse.h, Browse.cpp
* DbCore.h, DbCore.cpp
* FileSystem.h, FileSystem.cpp
* Storage.h, Storage.cpp
* Version.h, Version.cpp
* Queries.h, Queries.cpp
* Process.h, Process.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 March 2018
*/

#include "BrowseDefinitions.h"
#include "../DbCore/DbCore.h"
#include "../VersionComponent/Version.h"
#include "../FileSystem/FileSystem.h"
#include "../StorageComponent/Storage.h"
#include "../Queries/Queries.h"
#include "../Process/Process.h"


using namespace FileSystem;

namespace NoSqlDb
{
	template<typename T>
	class Browse
	{
	public:
		bool contain(const FileName& fileName);
		Dependencies& fileDependencies() { return _fileDependencies; }
		Dependencies fileDependencies() const { return _fileDependencies; }
		void fileDependencies(const Dependencies& dependencies) { _fileDependencies = dependencies; }
		FileList& fileList() { return _fileList; }
		FileList fileList() const { return _fileList; }
		void fileList(const FileList& fileList_) { _fileList = fileList_; }

		bool doBrowse(const DbElement<T>& el, Key& key, FileName& fileName);
		bool retrieveDependencies(const DbElement<T>& el, Key& key, FileName& fileName);
		FileName extractFileName(const FileName& fileName);
		void displayFile(FileName& fileName);
	private:
		Dependencies _fileDependencies;
		FileList _fileList;

	};

	//----< extract file name from a versioned file >----------------------------------

	template<typename T>
	FileName Browse<T>::extractFileName(const FileName& fileName)
	{
		Version v;
		return v.removeVersion(fileName);
	}

	//----< do dependencies contain this file? >----------------------------------

	template<typename T>
	bool Browse<T>::contain(const FileName& fileName)
	{
		if (std::find(fileDependencies().begin(), fileDependencies().end(), fileName) != fileDependencies().end())
			return true;
		return false;
	}

	//----< visit names of all packages on a dependency (sub)tree >----------------------------------

	template<typename T>
	bool Browse<T>::retrieveDependencies(const DbElement<T>& el, Key& key, FileName& fileName)
	{
		Storage storage;
		//DbProvider dbp;
		DbCore<PayLoad> db;
		db[key] = el;
		fileList().push_back(key);
		Dependencies dependencies = db[key].children();

		// find dependencies
		if (dependencies.empty())
		{
			std::cout << "\nThere're no dependecies of " << fileName << "\n";
			return true;
		}
		for (FileName dep : dependencies)
		{
			std::vector<FileName> files = Directory::getFiles(storage.storagePath(), dep);
			if (files.empty())
			{
				std::cout << "\n" << dep << " is not present in the Repository\n";
				return false;
			}
			if (db.contains(key))
			{
				std::cout << "\nDependencies are: " << dep << "\n";
				fileDependencies().push_back(dep);
				retrieveDependencies(db[dep], dep, dep);
			}
			return false;
		}
		return true;
	}

	//----< displays package descriptions >----------------------------------

	template<typename T>
	void Browse<T>::displayFile(FileName& fileName)
	{
		Storage storage;
		Process p;
		p.title("test application");
		std::string appPath = "c:/windows/system32/notepad.exe";
		p.application(appPath);
		std::cout << "\nSpawning a Filename: " << fileName << "\n";
		std::string cmdLine = "/A " + storage.storageFilePath(fileName);
		p.commandLine(cmdLine);
		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
		CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
		p.setCallBackProcessing(callback);
		p.registerCallback();

		std::cout << "\n  after OnExit";
		std::cout.flush();
		char ch;
		std::cin.read(&ch, 1);
	}

	//----< supports traversal of package dependency identified by a query on the NoSql database that holds metadata for all packages in the repository. >----------------------------------

	template<typename T>
	bool Browse<T>::doBrowse(const DbElement<T>& el, Key& key, FileName& fileName)
	{
		DbCore<PayLoad> db;
		db[key] = el;
		Query<PayLoad> q(db);
		Conditions<PayLoad> conds1;
		conds1.name(".*" + fileName + ".*");
		std::cout << "\n\nQuery command: conds1.name(\".*" + fileName + ".*\");\n";
		std::cout << "\n\nQuery command: q1.select(conds1);\n";
		q.select(conds1);
		putLine(2);
		Utilities::title("Browsing package file : " + key);
		putLine(2);
		if (!db.contains(key))
			return false;
		bool result = retrieveDependencies(db[key], key, fileName);
		if (fileDependencies().size() == 0)
		{
			std::cout << "\nDependencies are not present in the RepoStorage \n";
			for (FileName file : fileList())
			{
				showHeader();
				showRecord(fileName, db[key]);
				displayFile(file);
			}
			return true;
		}
		std::cout << "\n Displaying the metadata for all packages in the repository\n";
		showHeader();
		showRecord(fileName, db[key]);
		displayFile(key);

		return result;
	}
}