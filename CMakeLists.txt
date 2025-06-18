cmake_minimum_required(VERSION 3.16)
project(ANYad)

add_compile_options(-std=c++17)
add_executable(ad src/main.cpp src/dual.cpp)

add_subdirectory(tests)
enable_testing()
set(CTEST_OUTPUT_ON_FAILURE 1)
add_test(NAME "DualArithmetic" COMMAND ./tests/test_dual_arith)
