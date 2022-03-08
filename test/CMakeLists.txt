add_executable (MinCTestTestRunner "testrunner.c")
target_link_libraries (MinCTestTestRunner PRIVATE MinCTest)

target_include_directories (MinCTestTestRunner
  PRIVATE
    "./"
)

add_subdirectory ("./basic")
