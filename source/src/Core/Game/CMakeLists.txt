include_guard()
message("-- Reading file ${CMAKE_CURRENT_LIST_FILE}")

set(GAME_CPP_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp")
message("-- Checking file path: ${GAME_CPP_FILE_PATH}")
if(EXISTS "${GAME_CPP_FILE_PATH}")
  message("-- Game.cpp found!")
else()
  message("-- Game.cpp not found!")
endif()

set(GAME_H_DIR_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../include/Core")
message("-- Checking directory path: ${GAME_H_DIR_PATH}")
if(EXISTS "${GAME_H_DIR_PATH}")
  message("-- Directory path to /include found!")
else()
  message("-- Directory path to /include not found!")
endif()


add_library(Game "${GAME_CPP_FILE_PATH}")
target_include_directories(Game PUBLIC "${GAME_H_DIR_PATH}")
