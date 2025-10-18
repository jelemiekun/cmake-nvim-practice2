message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

add_library(Game "${CMAKE_CURRENT_LIST_DIR}/Game.cpp")
target_include_directories(Game PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../include/Core")

if (TARGET Game)
  message(STATUS "Target Game successfully created.")
else()
  message(WARNING "Target Game failed to create.")
endif()
