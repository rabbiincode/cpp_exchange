cmake_minimum_required(VERSION 3.20)

project(trading VERSION 0.1.0 LANGUAGES CXX)

add_executable(exchange src/main.cpp)

target_compile_features(exchange PRIVATE cxx_std_20)
set_target_properties(exchange PROPERTIES
    CXX_EXTENSIONS OFF
)

target_include_directories(exchange PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(exchange PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
    )
elseif(MSVC)
    target_compile_options(exchange PRIVATE /W4 /permissive-)
endif()
