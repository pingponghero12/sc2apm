cmake_minimum_required(VERSION 3.10)
project(sc2apm CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(sc2apm ${SOURCES})
target_link_libraries(sc2apm ${CURSES_LIBRARIES})
