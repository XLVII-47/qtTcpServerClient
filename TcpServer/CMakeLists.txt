cmake_minimum_required(VERSION 3.14)

project(TcpServer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(TcpServer
  main.cpp
  tcpserverhandler.h tcpserverhandler.cpp
  tcpserver.h tcpserver.cpp
  connectionworker.h connectionworker.cpp
)

target_link_libraries(TcpServer Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

install(TARGETS TcpServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
