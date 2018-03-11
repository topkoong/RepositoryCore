#pragma once
/////////////////////////////////////////////////////////////////////////////////////
// CheckinDefinitions.h - define aliases used throughout NoSqlDb namespace		   //
// ver 1.0																		   //
//                                                                                 //
// Environment : C++ Console Application                                           //
// Platform    : Windows 10 Home x64, Lenovo IdeaPad 700, Visual Studio 2017       //
// Application :  NoSqlDb Key/Value database prototype for CSE687-OOD, Spring 2018 //  
// Author: Theerut Foongkiatcharoen, EECS Department, Syracuse University          //
//         tfoongki@syr.edu                                                        //
/////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <string>
namespace NoSqlDb
{
	// type aliases with semantic meaning
	using FileSpec = std::string;    // c:/.../category/filename
	using FileRef = std::string;     // category/filename
	using FileName = std::string;    // filename may have version number at end
	using FullPath = std::string;    // full path with no filename
	using DirName = std::string;    // directory name 
}