message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

function(setup_standard_project)
  message(STATUS "Setting up standard project...")

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

  message(STATUS "Standard project setup done.")
endfunction()

function(find_packages)
  message(STATUS "Finding packages: ${ARGV}")

  foreach(package IN ITEMS ${ARGV})
    find_package(${package} REQUIRED CONFIG)
    message(STATUS "Package ${package} found.")
  endforeach()

  message(STATUS "Packages finding process done.")
endfunction()

function(create_source_libraries)
  message(STATUS "Creating source libraries...")

  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Game")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Vendors/glad")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Shader")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Practice")

  message(STATUS "Source libraries created.")
endfunction()

function(create_executables)
  message(STATUS "Creating executables...")

  add_executable(GameExe "${CMAKE_SOURCE_DIR}/src/Core/main.cpp")

  message(STATUS "Executabled created.")
endfunction()

function(link_all)
  message(STATUS "Linking all targets...")

  target_link_libraries(GameExe PUBLIC spdlog::spdlog SDL2::SDL2 Game)
  target_link_libraries(Game PUBLIC spdlog::spdlog SDL2::SDL2 glad Practice)
  target_link_libraries(Shader PUBLIC glad)
  target_link_libraries(Practice SDL2::SDL2 )

  message(STATUS "All targets linked.")
endfunction()
