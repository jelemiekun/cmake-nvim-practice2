message("-- Reading CMakeLists.txt from ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- Initiating ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")

add_library(game_cpp Game.cpp)
target_include_directories(game_cpp PUBLIC ${CMAKE_SOURCE_DIR}/include/Core)
