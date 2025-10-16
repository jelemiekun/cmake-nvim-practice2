include_guard()
message("-- Loading ${CMAKE_CURRENT_LIST_FILE}")

add_library(Game "${CMAKE_CURRENT_LIST_DIR}/Game.cpp")

if(TARGET Game)
  message("-- Game Library created")
else()
  message("-- Game Library failed to create")
endif()
