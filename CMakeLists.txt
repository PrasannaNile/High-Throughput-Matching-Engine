cmake_minimum_required(VERSION 3.10) # lastest version 
project(HighThroughputMatchingEngine VERSION 1.0) # name of project with version 

set(CMAKE_CXX_STANDARD 17) # force c++ 17 (smart pointers/ enum class)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # store final .exe file in bin

add_compile_options(-Wall -Wextra) # catch buggy logic strictly

include_directories(include) # header files from include folder

add_compile_definitions(CONCPP_BUILD_SHARED) # defines a global preprocessor macro

add_executable(HighThroughputMatchingEngine # single .exe file 
    src/main.cpp
    src/core/limitOrderBook.cpp
    src/core/priceLevel.cpp
)