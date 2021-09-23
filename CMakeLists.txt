cmake_minimum_required(VERSION 3.16)
project(TCPclient)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(PROJECT_SOURCES
        demo/main.cpp
        GUI/MainWindows/include/ConnectWindow.h
        GUI/MainWindows/include/MainWindow.h
        GUI/MainWindows/sources/ConnectWindow.cpp
        GUI/MainWindows/sources/MainWindow.cpp
        GUI/Settings/include/GUISettingsWindow.h
        GUI/Settings/sources/GUISettingsWindow.cpp
        GUI/Settings/include/StyleSettings.h
        GUI/Settings/sources/StyleSettings.cpp
        GUI/Submodules/include/style.h
        GUI/Submodules/include/switch.h
        GUI/Submodules/sources/switch.cpp
        )

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

add_library(GUI STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/sources/MainWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/sources/ConnectWindow.cpp
        )

target_include_directories(GUI PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/include>
        $<INSTALL_INTERFACE:include>
        )

file(COPY GUI/img DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(Settings STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/Settings/sources/GUISettingsWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/Settings/sources/StyleSettings.cpp
        )

target_include_directories(Settings PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/GUI/Settings/include>
        $<INSTALL_INTERFACE:include>
        )

add_library(Submodules STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/Submodules/sources/switch.cpp
        )

target_include_directories(Submodules PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/GUI/Submodules/include>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(Submodules Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

target_link_libraries(Settings Submodules)

target_link_libraries(GUI Settings)


add_executable(demo
        ${PROJECT_SOURCES}
        )

target_link_libraries(demo GUI)
