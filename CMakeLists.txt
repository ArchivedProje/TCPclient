cmake_minimum_required(VERSION 3.16)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(TCPclient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
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
        GUI/Settings/include/NetworkSettings.h
        GUI/Settings/sources/NetworkSettings.cpp
        GUI/Submodules/include/style.h
        GUI/Submodules/include/switch.h
        GUI/Submodules/sources/switch.cpp
        Network/include/Connection.h
        Network/sources/Connection.cpp
        RequestHandling/include/Handler.h
        RequestHandling/sources/Handler.cpp
        GUI/MainWindows/include/ServerWindow.h
        GUI/MainWindows/sources/ServerWindow.cpp
        GUI/Settings/include/Resizable.h
        GUI/Settings/sources/Resizable.cpp
        )

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

add_library(GUI STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/sources/MainWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/sources/ConnectWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/sources/ServerWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/sources/UsersWindow.cpp
        )

target_include_directories(GUI PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindows/include>
        $<INSTALL_INTERFACE:include>
        )

file(COPY GUI/img DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(Settings STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/Settings/sources/GUISettingsWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/Settings/sources/StyleSettings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/Settings/sources/NetworkSettings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/Settings/sources/Resizable.cpp
        )

file(COPY GUI/Settings/Config DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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

add_library(Network STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Network/sources/Connection.cpp
        )

target_include_directories(Network PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Network/include>
        $<INSTALL_INTERFACE:include>
        )

add_library(RequestHandling STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/RequestHandling/sources/Handler.cpp
        )

target_include_directories(RequestHandling PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/RequestHandling/include>
        $<INSTALL_INTERFACE:include>
        )

add_subdirectory(third-party/NetworkCommunication)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json REQUIRED)

hunter_add_package(Boost COMPONENTS system)
find_package(Boost CONFIG REQUIRED system)

target_link_libraries(RequestHandling nlohmann_json::nlohmann_json NetworkCommunication Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(Network Boost::system nlohmann_json::nlohmann_json NetworkCommunication Qt${QT_VERSION_MAJOR}::Widgets RequestHandling)

target_link_libraries(Submodules Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

target_link_libraries(Settings Submodules Network)

target_link_libraries(GUI Settings Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

add_executable(demo
        ${PROJECT_SOURCES}
        )

target_link_libraries(demo GUI)
