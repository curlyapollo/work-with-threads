cmake_minimum_required(VERSION 3.16)
project(chatters)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(chatters main.cpp)
