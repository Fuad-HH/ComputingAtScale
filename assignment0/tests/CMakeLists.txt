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


add_executable(test_matrix_read_write test_matrix_read_write.cpp)
target_link_libraries(test_matrix_read_write PRIVATE Catch2::Catch2WithMain matrix_mult)
target_include_directories(test_matrix_read_write PRIVATE ${CMAKE_SOURCE_DIR}/src)
catch_discover_tests(test_matrix_read_write
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)

add_executable(test_matrix_operations test_matrix_operations.cpp)
target_link_libraries(test_matrix_operations PRIVATE Catch2::Catch2WithMain matrix_mult)
target_include_directories(test_matrix_operations PRIVATE ${CMAKE_SOURCE_DIR}/src)
catch_discover_tests(test_matrix_operations
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)