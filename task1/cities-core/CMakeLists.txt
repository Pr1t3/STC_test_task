cmake_minimum_required(VERSION 3.16)

project(cities-core LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

add_library(cities-core STATIC
  cities-core_global.h
  city.h city.cpp
  citydao.h citydao.cpp
  databasemanager.h databasemanager.cpp
  citymodel.h citymodel.cpp
)

target_include_directories(cities-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cities-core PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)

target_compile_definitions(cities-core PRIVATE CITIES_CORE_LIBRARY)
