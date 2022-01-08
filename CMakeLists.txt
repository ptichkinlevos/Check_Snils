cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

project (SNILS)

find_package(Qt6 REQUIRED Sql)

add_executable (main SNILS/main.cpp)

target_link_libraries(main Qt6::Sql)
