cmake_minimum_required(VERSION 3.16)
project(ContactManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    contact.cpp
    contact.h
    contactmanager.cpp
    contactmanager.h
    adddialog.cpp
    adddialog.h
    adddialog.ui
    resources.qrc
)

add_executable(ContactManager
    ${PROJECT_SOURCES}
    styles.qss


)

target_link_libraries(ContactManager PRIVATE Qt6::Core Qt6::Widgets)
