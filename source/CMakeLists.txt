cmake_minimum_required(VERSION 3.20)

project(Practice_CMake LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(READY_TO_COMPILE FALSE)

message("-- Reading cmake file from ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src/Game)

include(Find_Packages.cmake)
find_packages()

if (READY_TO_COMPILE)
  message("-- Creating executable...")
  add_executable(GameExe src/main.cpp)

  target_link_libraries(GameExe PUBLIC GameLib spdlog::spdlog)
else()
  message("-- Failed to create an executable.")
endif()
