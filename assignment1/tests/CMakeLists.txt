################################## Catch2 ########################
find_package(Catch2 3 QUIET)
if(Catch2_FOUND)
    message(STATUS "Found Catch2: ${Catch2_DIR}")
else()
    message(STATUS "Catch2 not found. Fetching Catch2...")
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.4.0 # or a later release
    )
    FetchContent_MakeAvailable(Catch2)
endif()

###################################################################

##################### Catch2 Integration #####################
include(CTest)
include(Catch)
enable_testing()
##################### Catch2 Integration #####################
add_executable(unit_tests test_polynomial_class.cpp
        test_integrators.cpp
        test_file_reader.cpp)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain numerical_integrator)
catch_discover_tests(unit_tests
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)