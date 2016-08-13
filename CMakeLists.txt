cmake_minimum_required(VERSION 3.6)
project(KeeReeng)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_PREFIX_PATH "/home/daniele/Applicazioni/Qt/5.7/gcc_64")
find_package(Qt5Core      5.7 REQUIRED)
set(CMAKE_AUTOMOC ON)

add_subdirectory(src)