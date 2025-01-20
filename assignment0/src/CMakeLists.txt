add_library(matrix_mult matrix.cpp mmio.c)
target_include_directories(matrix_mult PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(multiplicationDriver main.cpp)
target_link_libraries(multiplicationDriver PRIVATE matrix_mult)
target_include_directories(multiplicationDriver PRIVATE ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(multiplicationDriver PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)