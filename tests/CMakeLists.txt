add_subdirectory(lib/cppunitlite)
add_executable(test_dual_arith test_dual_arith.cpp ../src/dual.cpp)
target_link_libraries(test_dual_arith PUBLIC cppunitlite)
target_include_directories(test_dual_arith PUBLIC ../src lib)
