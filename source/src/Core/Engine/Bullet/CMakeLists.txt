message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

add_library(Bullet "${CMAKE_CURRENT_LIST_DIR}/Bullet.cpp")
target_include_directories(Bullet PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../../include/Core/Engine")

if (UNIX)

else()
  commands

if (TARGET Bullet)
  message(STATUS "Target Bullet successfully created.")
else()
  message(WARNING "Target Bullet failed to create.")
endif()
