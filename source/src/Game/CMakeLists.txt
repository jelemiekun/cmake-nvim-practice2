include_guard()
message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

add_library(Game "${CMAKE_CURRENT_LIST_DIR}/Game.cpp")

if(TARGET Game)
  message(STATUS "Game Library created")
else()
  message(STATUS "Game Library failed to create")
endif()
