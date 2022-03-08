add_executable (TestRunner "testrunner.c")
target_link_libraries (TestRunner PRIVATE MinCTest)

target_include_directories (TestRunner
  PRIVATE
    "./"
)

add_subdirectory ("./basic")
