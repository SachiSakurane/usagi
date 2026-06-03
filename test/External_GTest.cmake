cmake_minimum_required(VERSION 3.16)

include(FetchContent)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
if(WIN32 AND USAGI_ENABLE_SKIA_TESTS)
        set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
else()
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main)
FetchContent_MakeAvailable(googletest)

set(GTEST_INCLUDE_DIRS)
set(GMOCK_INCLUDE_DIRS)
set(GTEST_LIBRARY gtest)
set(GTEST_MAIN_LIBRARY gtest_main)
set(GMOCK_LIBRARY gmock)
set(GMOCK_MAIN_LIBRARY gmock_main)
