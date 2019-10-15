cmake_minimum_required(VERSION 3.15)
project(Customer_Assistant)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(
        Customer_Assistant
        main.cpp
        resource/res.qrc
        src/mainwindow.cpp
        src/mainwindow.h
        src/preference.cpp
        src/preference.h
        src/about.cpp
        src/about.h
)
target_link_libraries(Customer_Assistant PRIVATE Qt5::Widgets)
