#ifndef DEFINITIONS_H
#define DEFINITIONS_H
/////////////////////////////////////////////////////////////////////////////////////
// VersionComponentDefinition.h - define aliases used throughout NoSqlDb namespace //
// ver 1.0                                                                         //
//                                                                                 //
// Environment : C++ Console Application                                           //
// Platform    : Windows 10 Home x64, Lenovo IdeaPad 700, Visual Studio 2017       //
// Application :  NoSqlDb Key/Value database prototype for CSE687-OOD, Spring 2018 //  
// Author: Theerut Foongkiatcharoen, EECS Department, Syracuse University          //
//         tfoongki@syr.edu                                                        //
/////////////////////////////////////////////////////////////////////////////////////
#include <unordered_map>
#include <string>

namespace NoSqlDb
{
	// type aliases with semantic meaning
	using FileSpec = std::string;    // c:/.../category/filename
	using FileRef = std::string;     // category/filename
	using FileName = std::string;    // filename may have version number at end
	using FullPath = std::string;    // full path with no filename
	using DirName = std::string;     // directory name 
	using Key = std::string;         // Dictionary key with format category.fileName
	using VerNum = std::int32_t;       // Dictionary value
	using CurrentVersion = std::unordered_map<Key, VerNum>;
	using iterator = typename CurrentVersion::iterator;
}
#endif
