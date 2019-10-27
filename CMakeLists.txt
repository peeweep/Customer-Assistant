cmake_minimum_required(VERSION 3.12.4)
project(Customer_Assistant)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
IF (CMAKE_HOST_APPLE)
    #    set(Qt5_DIR "$(brew --prefix qt5)/lib/cmake/Qt5")
    set(Qt5_DIR "/usr/local/opt/qt/lib/cmake/Qt5")
ENDIF ()
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
        src/errorDialog.cpp
        src/errorDialog.h
        src/couponList.cpp
        src/couponList.h
)
target_link_libraries(Customer_Assistant PRIVATE Qt5::Widgets)
