cmake_minimum_required(VERSION 3.20)

project(trading VERSION 0.1.0 LANGUAGES CXX)

add_executable(exchange src/main.cpp)
add_executable(domain_tests tests/domain_tests.cpp)

target_compile_features(exchange PRIVATE cxx_std_20)
target_compile_features(domain_tests PRIVATE cxx_std_20)

set_target_properties(exchange domain_tests PROPERTIES
    CXX_EXTENSIONS OFF
)

target_include_directories(exchange PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)
target_include_directories(domain_tests PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

enable_testing()
add_test(NAME domain_tests COMMAND domain_tests)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(exchange PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
    )
    target_compile_options(domain_tests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
    )
elseif(MSVC)
    target_compile_options(exchange PRIVATE /W4 /permissive-)
    target_compile_options(domain_tests PRIVATE /W4 /permissive-)
endif()
