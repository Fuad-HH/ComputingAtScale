add_library(polynomials polynomials.cpp)
target_include_directories(polynomials PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(numerical_integrator NumericalIntegrator.cpp)
target_include_directories(numerical_integrator PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(numerical_integrator PUBLIC polynomials)

add_executable(polynomial_integrate main.cpp)
target_link_libraries(polynomial_integrate PRIVATE polynomials)
target_include_directories(polynomial_integrate PRIVATE ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(polynomial_integrate PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)