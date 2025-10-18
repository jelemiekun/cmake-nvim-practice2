message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

function(setup_standard_project)
  message(STATUS "Setting up standard project...")

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  message(STATUS "Standard project setup done.")
endfunction()

function(find_packages)
  message(STATUS "Finding packages: ${ARGV}")

  foreach(package IN ITEMS ${ARGV})
    find_package(${package} REQUIRED)
    message(STATUS "Package ${package} found.")
  endforeach()

  message(STATUS "Packages finding process done.")
endfunction()

function(create_source_libraries)
  message(STATUS "Creating source libraries...")

  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Game")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Vendors/glad")

  message(STATUS "Source libraries created.")
endfunction()

function(create_executables)
  message(STATUS "Creating executables...")

  add_executable(GameExe "${CMAKE_SOURCE_DIR}/src/Core/main.cpp")

  message(STATUS "Executabled created.")
endfunction()

function(link_all)
  message(STATUS "Linking all targets...")

  target_link_libraries(GameExe PUBLIC spdlog::spdlog Game)
  target_link_libraries(Game PUBLIC spdlog::spdlog glad)

  message(STATUS "All targets linked.")
endfunction()
