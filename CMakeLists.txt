cmake_minimum_required(VERSION 3.21)

project(septemberfamilytree VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(septemberfamilytree
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(septemberfamilytree PRIVATE Qt6::Widgets)

install(TARGETS septemberfamilytree
    RUNTIME DESTINATION bin
)

install(FILES org.oneal.SeptemberFamilyTree.desktop
    DESTINATION share/applications
)

install(FILES org.oneal.SeptemberFamilyTree.svg
    DESTINATION share/icons/hicolor/scalable/apps
)

install(FILES org.oneal.SeptemberFamilyTree.metainfo.xml
    DESTINATION share/metainfo
)
