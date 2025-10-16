cmake_minimum_required(VERSION 3.20)

project(Practice VERSION 1.0.0 LANGUAGES CXX C)

message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(Sources)
include(Practice)

if (COMMAND find_packages)
  find_packages()
endif()

# Build Source Libraries
add_subdirectory(src/Game)

add_executable(GameExe src/main.cpp)

if(COMMAND link_all)
  link_all()
endif()
