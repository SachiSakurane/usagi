cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif ()

if (NOT (MSVC))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif ()

set(TEST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_StaticTest)

file(GLOB_RECURSE TEST_PROJECT_SOURCES *.cpp)
add_executable(${TEST_PROJECT_NAME} ${TEST_PROJECT_SOURCES})

target_include_directories(${TEST_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)
