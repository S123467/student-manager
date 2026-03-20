cmake_minimum_required(VERSION 3.5)

project(StudentManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(StudentManager
    main.cpp
    mainwindow.cpp
    mainwindow.h
    student.cpp
    student.h
    datamanager.cpp
    datamanager.h
)

target_link_libraries(StudentManager Qt5::Widgets)
