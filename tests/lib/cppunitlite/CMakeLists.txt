add_compile_options(-std=c++17 -Wno-deprecated)
add_library(cppunitlite 
    Test.cpp
    TestRegistry.cpp
    TestResult.cpp
    TestResultStdErr.cpp
    Success.cpp
    Failure.cpp
)
