include_guard()
message("-- Loading ${CMAKE_CURRENT_LIST_FILE}")

function(find_packages)
  message("-- Finding packages...")
  find_package(spdlog REQUIRED)

  if (TARGET spdlog::spdlog)
    message("-- spdlog found")
  else()
    message("-- spdlog not found")
  endif()

  message("-- Packages found")
endfunction()

function(link_all)
  message("-- Linking all targets...")
  target_include_directories(Game PUBLIC "${CMAKE_SOURCE_DIR}/include/Core")
  target_link_libraries(GameExe PUBLIC spdlog::spdlog Game)
  target_link_libraries(Game PUBLIC spdlog::spdlog)
  message("-- All targets linked")
endfunction()
