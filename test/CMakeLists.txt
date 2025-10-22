cmake_minimum_required(VERSION 3.16)

include(External_GTest.cmake)
include(GoogleTest)
find_package(Threads REQUIRED)

set(TEST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_Test)

file(GLOB_RECURSE TEST_PROJECT_SOURCES *.cpp)
add_executable(${TEST_PROJECT_NAME} ${TEST_PROJECT_SOURCES})

target_link_libraries(${TEST_PROJECT_NAME} PRIVATE
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
    ${GMOCK_LIBRARY}
    Threads::Threads
)

target_include_directories(${TEST_PROJECT_NAME} PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_dependencies(${TEST_PROJECT_NAME} googletest)

# ✅ discover tests dynamically at ctest runtime
gtest_discover_tests(
    ${TEST_PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DISCOVERY_TIMEOUT 10
)
