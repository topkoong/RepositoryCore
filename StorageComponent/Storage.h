#pragma once
/////////////////////////////////////////////////////////////////////////////////////
// Storage.h - Storage management for storing packages    						   //
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
* This package contains a class Storage with public functions and a struct RepoEnvironment:
* - createStorage     : creates specified folder on storage path
* - stagingPath       : string staging path including stagingDir (local storage)
* - stagingFilePath   : returns fully qualified fileName in staging path
* - storagePath       : string storage path including storageDir (repo storage)
* - storageFilePath   : returns fully qualified fileName in storage path
* - modifyFile        : copies file from staging to storage after addding a version number equal to the existing version number
* - addFile           : copies file from staging to storage after adding a version number one higher than existing version number
* - retrieveFile      : copies file from storage to staging and removes version
* - findFile          : returns versioned name of file found in category
* - findVersions      : returns list of all versions of specified file

* Required Files:
* ---------------
* StorageDefinitions.h, Storage.h, Storage.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 28 Feb 2018
*/
#include "StorageDefinitions.h"

namespace NoSqlDb
{
	class Storage
	{
	public:
		Storage(){}
		bool createStorage(const FullPath& path);
		FullPath stagingPath(DirName subfolder = "");
		FileSpec stagingFilePath(FileName& fileName);
		FullPath storagePath(DirName subfolder = "");
		FileSpec storageFilePath(FileName& fileName);
		bool addFile(FileName srcFile, FileName dstFile = "", bool move = true);
		bool modifyFile(FileName srcFile, FileName dstFile = "", bool move = true);
		bool retrieveFile(FileName& srcFile);
		FileSpec findFile(FileName& fileName);
		std::vector<FileSpec> findVersions(FileName& fileName);
		bool deleteFile(FileName& fileName);
		~Storage() {}
	};
	struct RepoEnvironment
	{
		StoragePath repoPath() { return repoPath_; }
		StoragePath localPath() { return stagingPath_; }
	private:
		StoragePath repoPath_ = "../RepoStorage";
		StagingPath stagingPath_ = "../StagingStorage";
	};

}
