# Software Repository Testbed (C++)
### The Repository is intended to manage a, possibly large, collection of source code packages, providing versioning, check-in, check-out, and browsing.

#### NoSql databased stores metadata about each file in the repository. Version numbers will be appended to file names on check-in. All other information will be contained in metadata, e.g., description, author, check-in status (open or closed), files on which it depends, categories to which the file belongs, and its storage path in the Repository.
- [x] Package prologues and function prologues are included.
- [x] The public interface documentation — holding a short description of the package operations, the required files to build the package, and the build process and the maintenance history — is included.
- [x] Each funtion includes some comments to describe its operation.

1. provide C++ packages.
   1. TestExecutive: executes a sequence of tests to demonstrate core Repository functionality.
   1. RepositoryCore: provides means to check-in, version, browse, and check-out source code packages.
   1. Check-in: provides the functionality to start a new package version by accepting files, appending version numbers to their filenames, providing dependency and category information, creating metadata, and storing the files in a designated location.
   1. Check-out: retrieves package files, removing version information from their filenames. Retrieved files will be copied to a specified directory.
   1. Version: manages version numbering for all files held in the Repository.
   1. Browse: provides the capability to locate files and view their contents.
1. support support check-in by accepting a single package's files3 and append a version number to the end of each file name, e.g., p5.h and p5.cpp become p5.h.3 and p5.cpp.3 if the package name is p5 and the last closed check-in for that package was version 2. A check-in is open, by default. A package with open check-in can be modified without altering its version number. Once a check-in is closed, that version of the package becomes immutable.
   1. The author of a check-in defines all of the packages that the check-in package depends on. However, a check-in can only be closed if its dependent packages are all present in the Repository, with closed check-ins.
1. support browsing of one or more packages by displaying package descriptions. The packages to be browsed are identified by a query on the NoSql database that holds metadata for all packages in the repository. The full package text shall be displayed on demand, identified by one of the keys returned from the initial browse query.

> Each package is accompanied with a test stub in which it is the piece of code used to test each package against different cases, and it is done independently.

