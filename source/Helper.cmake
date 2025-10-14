message("-- Loading file ${CMAKE_CURRENT_LIST_FILE}")

function(find_packages)
  message("-- Finding packages...")

  find_package(spdlog REQUIRED)

  if (TARGET spdlog::spdlog)
    message("-- Package spdlog successfully found.")
  else()
    message("-- Package spdlog failed to find.")
  endif()
endfunction()
