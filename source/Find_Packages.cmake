include_guard()

message("-- Reading cmake file from ${CMAKE_CURRENT_LIST_FILE}")

function(find_packages)
  message("-- Finding packages...")

  message("-- Finding spdlog package...")
  find_package(spdlog REQUIRED)

  if (TARGET spdlog::spdlog)
    message("-- spdlog package exists!")
    set(READY_TO_COMPILE TRUE PARENT_SCOPE)
  else()
    message("-- spdlog package failed to find!")
  endif()
endfunction()
