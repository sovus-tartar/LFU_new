cmake_minimum_required(VERSION 3.0.0)
project(lfu VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(lfu ./source/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  str_tester
  ./tests/data_test/str_tester.cpp
)
target_link_libraries(
  str_tester
  GTest::gtest_main
)

add_executable(
  unit_tester
  ./tests/tester.cpp
)
target_link_libraries(
  unit_tester
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(str_tester)
gtest_discover_tests(unit_tester)