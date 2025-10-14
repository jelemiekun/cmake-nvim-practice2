message("-- Reading cmake file from ${CMAKE_CURRENT_SOURCE_DIR}")

set(libName GameLib)

message("-- Creating ${libName} with Game.cpp")

add_library(${libName} Game.cpp)
target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Core)

if(TARGET ${libName})
  message("-- Library ${libName} created successfully.")
else()
  message("-- Library ${libName} failed to create.")
endif()
