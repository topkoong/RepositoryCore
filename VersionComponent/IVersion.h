#pragma once
/////////////////////////////////////////////////////////////////////////////////////
// IVersion.h - interface for versioning repository contents					   //
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

#include <string>
#include "VersionDefinitions.h"
namespace NoSqlDb
{
	class IVersion
	{
	public:
		virtual bool contain(const Key& key) = 0;
		virtual bool hasVersion(const FileName& fileName) = 0;
		virtual FileName addVersion(const FileName& fileName) = 0;
		virtual FileName removeVersion(const FileName& fileName) = 0;
		virtual VerNum getVersion(const FileName& fileName) = 0;
		virtual int getLatestVersion(FileName& fileName) = 0;
		virtual void restoreVersionsFromFiles() = 0;
		virtual ~IVersion() {}
	};
}
