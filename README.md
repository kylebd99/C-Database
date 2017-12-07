# C-Database
This program is a commandlet which will allow you to do a basic analysis of a CSV file from the command line. It can either be run as a .exe file directly or it can be compiled from the source code. Furthermore, the file "Database_Helpers.cc" can be used as a header file to use the Database class and associated functions in your own programs.

1) Running as a .exe file
  -First, download the file "CSV_Reader.exe"
  -Open a terminal or command line
  -Enter the command "cd FILE_LOC" where FILE_LOC is the address of the folder that you downloaded
   the program into
  -Enter the command "./CSV_Reader.csv 'CSV_FILE'" where CSV_FILE is the address of
   the file that you would like to analyze
2) Compiling
  -First, make sure that you have a recent version of the compiler g++ and that
   you have the Boost Library, specifically "boost/variant.hpp" and "boost/tokenizer.hpp"
  -Download the files "Database_Class.cc", "Database_Helpers.cc", and "CSV_Reader.cc"
  -Enter the command "cd FILE_LOC" where FILE_LOC is the address of the folder that you downloaded
   the files into
  -Compile "CSV_Reader.cc" using the command "g++ -o CSV_Reader.exe CSV_Reader.cc"
  -Enter the command "./CSV_Reader.csv 'CSV_FILE'" where CSV_FILE is the address of
   the file that you would like to analyze
3) Using in another program
  -First, make sure that you have a recent version of the compiler g++ and that
   you have the Boost Library, specifically "boost/variant.hpp" and "boost/tokenizer.hpp"
  -Download the files "Database_Class.cc" and "Database_Helpers.cc"
  -Make sure that they can be found by your compiler by either putting them into the compiler's
   input path or placing them into the same folder as your program
  -Place "#include "Database_Helpers.cc"" at the top of your program to include
   all classes and functions in both the files
