cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

include(External_GTest.cmake)
include(GoogleTest)
find_package(Threads REQUIRED)

if (NOT (MSVC))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

set(TEST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_Test)

add_executable(${TEST_PROJECT_NAME}
        main.cpp
        concepts/geometry/point_concept.cpp
        concepts/geometry/rect_concept.cpp
        concepts/geometry/size_concept.cpp
        concepts/graphics/color_concept.cpp
        concepts/graphics/draw_contextable.cpp
        concepts/ui/clickable.cpp
        concepts/ui/drawable.cpp
        geometry/point/function.cpp
        geometry/point/operator.cpp
        geometry/point/point.cpp
        geometry/rect/function.cpp
        geometry/rect/operator.cpp
        geometry/rect/rect.cpp
        geometry/size/function.cpp
        geometry/size/operator.cpp
        geometry/size/size.cpp
        graphics/color/color.cpp
        variable/variable_traits.cpp
        variable/variable.cpp)

if (MSVC)
    target_link_libraries(${TEST_PROJECT_NAME} PRIVATE
            ${GTEST_LIBRARY}
            ${GMOCK_LIBRARY}
            Threads::Threads)
else()
    target_link_libraries(${TEST_PROJECT_NAME} PRIVATE
            ${GTEST_LIBRARY}
            ${GMOCK_LIBRARY}
            pthread)
endif()

target_include_directories(${TEST_PROJECT_NAME} PRIVATE
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

if (MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${TEST_PROJECT_NAME} PRIVATE /W4 /WX /MTd)
    else()
        target_compile_options(${TEST_PROJECT_NAME} PRIVATE /W4 /WX /MT)
    endif()
else ()
    target_compile_options(${TEST_PROJECT_NAME} PRIVATE -Wall -W)
endif()

gtest_add_tests(
        TARGET      ${TEST_PROJECT_NAME}
        TEST_LIST   ${TEST_PROJECT_NAME}_Targets)

# set each target to timeout if not finished within 10 sec
set_tests_properties(${${TEST_PROJECT_NAME}_Targets} PROPERTIES TIMEOUT 10)
