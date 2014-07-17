Minesense
=========
This is an implementation of the client and server that communicate using the Common Data Format (CDF).

Tools and Dependencies
======================
The code was compiled using Visual Studio 2013 (Express Edition).
The project was created using CMake 3.0.0 with the Visual Studio 12 2013 Win64 option.
The external dependencies used are boost 1.55.0, Qt 5.3.1, and Google Test 1.7.0.
You will need to set the paths for boost and Qt on your own system in order to run CMake successfully.

Building Google Test
====================
The CMakeLists.txt file in the root of Google Test was used with the following additions at line 70:

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_DEBUG_POSTFIX "d")

This makes Google Test work better with the find_package macro from CMake.
