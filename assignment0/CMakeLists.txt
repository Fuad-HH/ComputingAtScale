cmake_minimum_required(VERSION 3.26)
project(assignment0 CXX C)

include(FetchContent)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS False)

########################## OPTIONS ###########################################
option(BUILD_SHARED_LIBS                    "Build shared libraries"        ON)
option(ASSIGNMENT0_BUILD_TESTS              "Build tests"                   ON)

add_subdirectory(src)

if(ASSIGNMENT0_BUILD_TESTS)
    message(STATUS "Tests enabled")
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# For now: not installing anything