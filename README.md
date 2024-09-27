# Laboratory work #1, OOP by dep12

Solve for variant #3 of laboratory work #1. This program works in 2 modes: 
+ Converts array of integers, array name and element tag to the XML-formatted string
+ Converst XML-formatted string to array of integers, extracting its name and element tag
Functions in library support 3 overloads:
+ const char*
+ const char* + size_t
+ std::string
Project also contain unit testing by Catch2, Doxygen documentation and MIT license.

# Files

├── **CMakeLists.txt**           -- _main CMake config_
├── lib
│   ├── **xml.cpp**				  -- _realization of library functions_
│   └── **xml.h**					  -- _prototypes of library functions_
├── **main.cpp**					  -- _main function_
└── tests
    ├── **CMakeLists.txt**		  -- _CMake config for unit testing_
    └── **testing.cpp**			  -- _Catch2 unit testing_

## How to use program

```bash
mkdir build # create build directory
cd build # move to build directory
cmake .. # build files generating based on CMakeLists.txt
make # running the Makefile
./bin # running the binary
```


## How to test program

```bash
mkdir build # create build directory
cd build # move to build directory
cmake .. # build files generating based on CMakeLists.txt
make # running the Makefile
./tests/testing # running the testing binary
gcovr -r ../ -e CMakeFiles --html-details -o coverage.html # creating coverage report
```


## How to compile documentation

```bash
doxygen doxygen_config_lab1 # generating documentation (./html/index.html) based on config file
```

## Contacts

+ LMS - filchukov.md
+ Telegram - t.me/mihafil746
+ E-Mail j32filchukov@gmail.com
