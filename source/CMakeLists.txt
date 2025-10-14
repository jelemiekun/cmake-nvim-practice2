cmake_minimum_required(VERSION 3.20)

project(CMakeExercise LANGUAGES CXX C)

message("-- Configuring CMake and CXX...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("-- Setting up variables...")
set(HELPER_INCLUSION_SUCCESS FALSE)
set(HELPER_FILE "Helper.cmake")

include(${HELPER_FILE} RESULT_VARIABLE HELPER_INCLUSION_SUCCESS)
if (HELPER_INCLUSION_SUCCESS)
  message("-- Successfully loaded ${HELPER_FILE}")
else()
  message("-- Failed to load ${HELPER_FILE}")
endif()

if (COMMAND find_packages)
  find_packages()
endif()

add_executable(GameExe src/main.cpp)
