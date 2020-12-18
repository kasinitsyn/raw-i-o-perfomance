cmake_minimum_required(VERSION 2.8)

project(stpoi)
add_executable(${PROJECT_NAME} "main.cpp" "test.hpp" "test.cpp")

add_library(hayai STATIC IMPORTED)
set_property(TARGET hayai PROPERTY IMPORTED_LOCATION "/usr/local/lib/libhayai_main.a")

target_link_libraries(${PROJECT_NAME} PUBLIC hayai)
