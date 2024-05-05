cmake_minimum_required(VERSION 3.7...3.24)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(VAR_ARRAY VERSION 1.0
    DESCRIPTION "Variadic Array"
    LANGUAGES CXX)

add_executable(var_array
    src/main.cc
)

target_compile_features(var_array PRIVATE cxx_std_17)
