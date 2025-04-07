cmake_minimum_required(VERSION 3.24)
project(coding_work)

set(CMAKE_CXX_STANDARD 26)

add_executable(coding_work main.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(tests split_test.cpp cache_test.cpp point_test.cpp)
target_link_libraries(tests gtest_main)
add_test(NAME split_tests COMMAND tests)
add_test(NAME cache_tests COMMAND tests)
add_test(NAME point_tests COMMAND tests)