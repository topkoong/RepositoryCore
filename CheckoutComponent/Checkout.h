#pragma once
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
* This package contains a class Checkout with public methods:
* - doCheckout				: copy all the package metadata and referred files from a dependency tree to the file Staging area
* - checkDependencies		: checks if check-in files have dependencies or not
* - extractFileName			: extract file name from a versioned file
* - retrieveDependencies	: visit names of all packages on a dependency (sub)tree
* - fileDependencies		: getter and setter of _fileDependencies
* - fileList				: getter and setter of _fileList
* 
* Required Files:
* ---------------
* CheckoutDefinitions.h, Checkout.h, Checkout.cpp
* DbCore.h, DbCore.cpp
* FileSystem.h, FileSystem.cpp
* Version.h, Version.cpp
* Storage.h, Storage.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 March 2018
*/

#include "CheckoutDefinitions.h"
#include "../DbCore/DbCore.h"
#include "../FileSystem/FileSystem.h"
#include "../VersionComponent/Version.h"
#include "../StorageComponent/Storage.h"

using namespace FileSystem;

namespace NoSqlDb
{
	template<typename T>
	class Checkout
	{
	public:
		Dependencies& fileDependencies() { return _fileDependencies; }
		Dependencies fileDependencies() const { return _fileDependencies; }
		void fileDependencies(const Dependencies& dependencies) { _fileDependencies = dependencies; }
		FileList& fileList() { return _fileList; }
		FileList fileList() const { return _fileList; }
		void fileList(const FileList& fileList_) { _fileList = fileList_; }
		bool doCheckout(const DbElement<T>& el, const FileName& fileName);
		bool retrieveDependencies(const DbElement<T>& el, const FileName& fileName);
		FileName extractFileName(const FileName& fileName);
	private:
		Dependencies _fileDependencies;
		FileList _fileList;
	};

	//----< extract file name from a versioned file >----------------------

	template<typename T>
	FileName Checkout<T>::extractFileName(const FileName& fileName)
	{
		Version v;
		return v.removeVersion(fileName);
	}

	//----< visit names of all packages on a dependency (sub)tree >----------------------

	template<typename T>
	bool Checkout<T>::retrieveDependencies(const DbElement<T>& el, const FileName& fileName)
	{
		Storage storage;
		DbCore<T> db;
		db[fileName] = el;
		// extract primary filename from metadata and add to fileList
		//FileName srcFile = extractFileName(fileName);
		fileList().push_back(fileName);
		Dependencies dependencies = db[fileName].children();

		// find dependencies
		if (dependencies.empty())
		{
			std::cout << "\nThere're no dependecies of " << fileName << "\n";
			return true;
		}
		for (FileName dep : dependencies)
		{
			//FileName file = extractFileName(dep);
			std::vector<FileName> files = Directory::getFiles(storage.storagePath(), dep);
			if (files.empty())
			{
				std::cout << "\n" << dep << " is not present in the Repository\n";
				return false;
			}
			if (db.contains(fileName))
			{
				std::cout << "\nDependencies are: " << dep << "\n";
				fileDependencies().push_back(dep);
				retrieveDependencies(db[dep], dep);
			}
			return false;
		}
		return true;
	}

	//----< copy all the package metadata and referred files from a dependency tree (file storage area) to the file Staging area >----------------------
	
	template<typename T>
	bool Checkout<T>::doCheckout(const DbElement<T>& el, const FileName& fileName)
	{
		DbCore<T> db;
		db[fileName] = el;
		Storage storage;
		putLine(2);
		Utilities::title("Retrieving package file : " + fileName);
		putLine(2);
		if (!db.contains(fileName))
			return false;
		bool result = retrieveDependencies(db[fileName], fileName);
		if (fileDependencies().size() == 0)
		{
			std::cout << "\nDependencies are not present in the RepoStorage \n";
			for (FileName file : fileList())
				storage.retrieveFile(file);
			return true;
		}
		for (FileName dfile : fileDependencies())
			storage.retrieveFile(dfile);
		for (FileName file : fileList())
			storage.retrieveFile(file);
		return result;
	}

}