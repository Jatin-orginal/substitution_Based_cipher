cmake_minimum_required(VERSION 3.16)
project(SubstitutionCipher)


Set(CMAKE_CXX_STANDARD 17)
Set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets) # or Qt5

add_executable(SubstitutionCipher main.cpp)
target_link_libraries(SubstitutionCipher PRIVATE Qt6::widgets)