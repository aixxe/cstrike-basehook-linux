cmake_minimum_required(VERSION 2.8)
project(cstrike-basehook)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -m32 -Wall -Wextra -Wpedantic")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++ -m32")

include_directories("include")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp include/*.cpp)

add_library(cstrike-basehook SHARED ${SOURCE_FILES})

target_link_libraries(cstrike-basehook SDL2 GL)
