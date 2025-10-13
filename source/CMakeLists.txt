cmake_minimum_required(VERSION 3.20)

project(Practice LANGUAGES C CXX)

message("-- Configuring CXX...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("-- Finding packages...")
find_package(spdlog REQUIRED)

message("-- Reading CMakeLists.txt from ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- Initiating top level CMakeLists.txt")

add_subdirectory(src/Game)

add_executable(GameExe src/main.cpp)

target_link_libraries(GameExe PUBLIC game_cpp spdlog::spdlog)
target_link_libraries(GameLib PUBLIC spdlog::spdlog)
