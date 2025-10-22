message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

add_library(Practice "${CMAKE_CURRENT_LIST_DIR}/Practice.cpp")
target_include_directories(Practice PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../../include/Core/Engine")

if (TARGET Practice)
  message(STATUS "Target Practice successfully created.")
else()
  message(WARNING "Target Practice failed to create.")
endif()
