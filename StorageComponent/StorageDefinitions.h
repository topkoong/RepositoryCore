#pragma once
#include <vector>
#include <string>
// type aliases with semantic meaning
namespace NoSqlDb
{
	using FileSpec = std::string;    // c:/.../category/filename
	using FileRef = std::string;     // category/filename
	using FileName = std::string;    // filename may have version number at end
	using FullPath = std::string;    // full path with no filename
	using DirName = std::string;   // directory name 
	using Dependencies = std::vector<FileName>;
	using StoragePath = std::string;
	using StagingPath = std::string;
}