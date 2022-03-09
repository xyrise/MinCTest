cmake_minimum_required (VERSION 3.13)

project (MinCTest
  VERSION 0.0.1
  DESCRIPTION "A minimal test runner designed for use with CTest in a CMake project."
  HOMEPAGE_URL "https://github.com/xyrise/MinCTest"
  LANGUAGES C
)

include(CTest)

set (CMAKE_C_STANDARD 90)
set (CMAKE_C_STANDARD_REQUIRED 90)

if (MSVC)
  add_compile_options(
    /Wall
    /WX
    /wd4710
    /wd4711
    /wd5045
    /wd4820
    /wd4706
    /wd4255
    /wd4090
    /Qspectre
  )
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library (MinCTest INTERFACE)

target_include_directories (MinCTest
  INTERFACE
    "./include"
)

add_subdirectory ("./test")
