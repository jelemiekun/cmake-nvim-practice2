message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

add_library(ImGUI "${CMAKE_CURRENT_LIST_DIR}/ImGUI.cpp")
target_include_directories(ImGUI PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../../include/Core/Engine")

if (TARGET ImGUI)
  message(STATUS "Target ImGUI successfully created.")
else()
  message(WARNING "Target ImGUI failed to create.")
endif()
