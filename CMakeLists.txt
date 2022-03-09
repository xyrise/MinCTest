cmake_minimum_required (VERSION 3.13)

project (MinCTest
  VERSION 0.0.2
  DESCRIPTION "A minimal test runner designed for use with CTest in a CMake project."
  HOMEPAGE_URL "https://github.com/xyrise/MinCTest"
  LANGUAGES C
)
set (PROJECT_NAME "MinCTest")
set (CMAKE_C_STANDARD 90)
set (CMAKE_C_STANDARD_REQUIRED 90)

add_library (${PROJECT_NAME} INTERFACE)

include (CTest)
include (cmake/CompileOptions.cmake)

target_include_directories (${PROJECT_NAME}
  INTERFACE
    "./include"
)

add_subdirectory ("./test")
