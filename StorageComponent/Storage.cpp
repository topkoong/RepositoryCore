/////////////////////////////////////////////////////////////////////////////////////
// Storage.cpp - Storage management for storing packages    					   //
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
* This package contains a class Storage with public functions:
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
* Storage.h, Storage.cpp
* FileSystem.h, FileSystem.cpp
* Version.h, Version.cpp
* StringUtilities.h, StringUtilities.cpp
*
* Build Process:
* --------------
* devenv Cpp11-NoSqlDb.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 28 Feb 2018
*/

#include "Storage.h"
#include "../FileSystem/FileSystem.h"
#include "../VersionComponent/Version.h"
#include "../Utilities/StringUtilities/StringUtilities.h"

using namespace NoSqlDb;
using namespace FileSystem;

/*----< create directory for storing packages >----------------*/

bool Storage::createStorage(const FullPath& path)
{
	if (!Directory::exists(path))
		Directory::create(path);
	return true;
}

/*----< returns path to client's staging path >---------------*/

FullPath Storage::stagingPath(DirName subfolder)
{
	RepoEnvironment repoEnv;
	return repoEnv.localPath() + subfolder;
}

/*----< add fileName to end of stagingPath >------------------*/

FileSpec Storage::stagingFilePath(FileName& fileName)
{
	return stagingPath() + "/" + fileName;
}

/*----< returns path to category in storage area >-------------*/

FullPath Storage::storagePath(DirName subfolder)
{
	RepoEnvironment repoEnv;
	return repoEnv.repoPath() + subfolder;;
}

/*----< add fileName to end of storagePath >-------------------*/

FileSpec Storage::storageFilePath(FileName& fileName)
{
	return storagePath() + "/" + fileName;
}

/*----< copy file from staging area to storage >-------*/
/*
*  srcFile is the name of file in stagingPath
*  dstFile is the name of the file to be moved to storagePath
*
*  addFile adds a version number to dstFile before putting in storage area
*  
*/

bool Storage::addFile(FileName srcFile, FileName dstFile, bool move)
{
	if (dstFile.length() == 0)
		dstFile = srcFile;
	Version v;
	FileName ver_dstFile = v.addVersion(dstFile);
	std::cout << "\n\n Adding a new version of : " << dstFile << "to" << ver_dstFile << "\n\n";
	FileSpec srcFileSpec = stagingFilePath(srcFile);
	FileSpec dstFileSpec = storageFilePath(ver_dstFile);
	bool ok;
	if (move)
	{
		try
		{
			File::copy(srcFileSpec, dstFileSpec);
			std::cout << "\n\nCopying file:" << srcFile << " from staging path: " << srcFileSpec << " to storage file path: " << dstFileSpec << "\n\n";
			ok = true;
		}
		catch (const std::exception& e)
		{
			std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
			ok = false;
		}
	}
	else
	{
		try
		{
			File::copy(srcFileSpec, dstFileSpec);
			std::cout << "\n\nCopying file:" << srcFile << " from staging path: " << srcFileSpec << " to storage file path: " << dstFileSpec << "\n\n";
			ok = true;
		}
		catch (const std::exception& e)
		{
			std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
			ok = false;
		}
	}
	return ok;

}

/*----< move or copy file from staging area to storage >-------*/
/*
*  srcFile is the name of file in stagingPath
*  dstFile is the name of the file to be moved to storagePath
*  modifyFile adds a version number equal to the existing version number
*  to dstFile before putting in storage area defined by category
 */

bool Storage::modifyFile(FileName srcFile, FileName dstFile, bool move)
{
	move = false;
	if (dstFile.length() == 0)
		dstFile = srcFile;
	Version v;
	VerNum ver = v.getLatestVersion(dstFile);
	FileName ver_dstFile = dstFile + "." + std::to_string(ver);
	std::cout << "\n\n Last checkin was open so just modify existing version, and a version number is equal to the existing version number: " << ver_dstFile << "\n\n";
	FileSpec srcFileSpec = stagingFilePath(srcFile);
	FileSpec dstFileSpec = storageFilePath(ver_dstFile);
	bool ok;
	if (move)
	{
		try
		{
			File::copy(srcFileSpec, dstFileSpec);
			std::cout << "\n\nCopying file: " << srcFile << " from staging path: " << srcFileSpec << " to storage file path: " << dstFileSpec << "\n\n";
			ok = true;
		}
		catch (const std::exception& e)
		{
			std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
			ok = false;
		}
	}
	try
	{
		File::copy(srcFileSpec, dstFileSpec);
		std::cout << "\n\nCopying file: " << srcFile << " from staging path: " << srcFileSpec << " to storage file path: " << dstFileSpec << "\n\n";
		ok = true;
	}
	catch (const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
		ok = false;
	}
	return ok;
}


/*----< copy file from storage to staging area >---------------*/
/*
* - srcFile is expected to be a file name, e.g., has no path
*/

bool Storage::retrieveFile(FileName& srcFile)
{
	FileSpec srcFileSpec = storageFilePath(srcFile);
	Version v;
	FileSpec dstFileSpec = v.removeVersion(srcFile);
	std::cout << "\n\n Removing a version from: " << srcFile << " to " << dstFileSpec << "\n\n";
	dstFileSpec = stagingFilePath(dstFileSpec);
	bool ok;
	try
	{
		File::copy(srcFileSpec, dstFileSpec);
		std::cout << "\n\nCopying file: " << srcFile << " from storage file path: " << srcFileSpec << " to staging path: " << dstFileSpec << "\n\n";
		ok = true;
	}
	catch (const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
		ok = false;
	}
	return ok;
}

/*----< find all versions of file in storage >----------------*/

FileSpec Storage::findFile(FileName& fileName)
{
	std::string foundName = "";
	Version v;
	// if not versioned, add latest version
	if (v.hasVersion(fileName))
	{
		VerNum ver = v.getLatestVersion(fileName);
		fileName = fileName + "." + std::to_string(ver);
	}
	RepoEnvironment repoEnv;
	std::vector<FileName> files = Directory::getFiles(repoEnv.repoPath());
	for (FileSpec file : files)
	{
		if (file == fileName)
		{
			foundName = fileName;
			break;
		}
	}
	return foundName;
}

/*----< find all versions of file in RepoStorage >----------------*/

std::vector<FileSpec> Storage::findVersions(FileName& fileName)
{
	Version v;
	if (v.hasVersion(fileName))
		fileName = v.removeVersion(fileName);
	RepoEnvironment repoEnv;
	std::vector<FileName> files = Directory::getFiles(repoEnv.repoPath(), fileName + "*");
	for (size_t i = 0; i < files.size(); ++i)
	{
		files[i] = Path::getName(files[i]);
	}
	return files;
}

/*----< delete file from storage >-----------------------------*/

bool Storage::deleteFile(FileName& fileName)
{
	if (!File::exists(fileName))
		return false;
	try
	{
		File::remove(fileName);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
		return false;
	}
}

bool testStorage()
{
	Storage storage;
	storage.stagingPath();
	return true;
}



#ifdef TEST_STORAGE
int main()
{
	Utilities::Title("Demonstrating Storage");
	putLine();

	TestExecutive ex;

	// define test structures with test function and message

	TestExecutive::TestStr ts1{ testStorage, "Storage testing" };


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