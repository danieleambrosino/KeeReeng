cmake_minimum_required(VERSION 3.6)
project(KeeReeng)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_PREFIX_PATH "/usr/lib/Qt/5.7/gcc_64")
find_package(Qt5Core      5.7 REQUIRED)
find_package(Qt5Widgets   5.7 REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories("${KeeReeng_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(test)