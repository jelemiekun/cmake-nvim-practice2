message("-- Reading CMakeLists.txt from ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- Initiating ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")

add_library(GameLib Game.cpp)
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Core)

