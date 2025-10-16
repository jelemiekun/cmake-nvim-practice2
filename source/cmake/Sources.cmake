include_guard()
message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

function(find_packages)
  message(STATUS "Finding packages...")
  find_package(spdlog REQUIRED)

  if (TARGET spdlog::spdlog)
    message(STATUS "spdlog found")
  else()
    message(STATUS "spdlog not found")
  endif()

  message(STATUS "Packages found")
endfunction()

function(link_all)
  message(STATUS "Linking all targets...")
  target_include_directories(Game PUBLIC "${CMAKE_SOURCE_DIR}/include/Core")
  target_link_libraries(GameExe PUBLIC spdlog::spdlog Game)
  target_link_libraries(Game PUBLIC spdlog::spdlog)
  message(STATUS "All targets linked")
endfunction()
