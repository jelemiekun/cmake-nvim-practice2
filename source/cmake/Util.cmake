message(STATUS "Loading ${CMAKE_CURRENT_LIST_FILE}")

function(setup_standard_project)
  message(STATUS "Setting up standard project...")

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

  if (WIN32 AND MSVC)
      add_compile_options("/utf-8")
  endif()

  message(STATUS "Standard project setup done.")
endfunction()

function(find_packages)
  message(STATUS "Finding packages: ${ARGV}")

  foreach(package IN ITEMS ${ARGV})
    if(UNIX)
        message(STATUS "Finding ${package} package for linux operating system...")
        find_package(${package} CONFIG REQUIRED)
    elseif(WIN32)
        message(STATUS "Finding ${package} package for windows operating system...")

        if(DEFINED ENV{VCPKG_ROOT})
            list(APPEND CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-windows")
        else()
            message(WARNING "VCPKG_ROOT not defined. Please set it or pass the toolchain file.")
        endif()

        find_package(${package} CONFIG REQUIRED)
    else()
        message(STATUS "Current operating system not ...")
    endif()
    message(STATUS "Package ${package} found.")
  endforeach()

  message(STATUS "Packages finding process done.")
endfunction()

function(create_source_libraries)
  message(STATUS "Creating source libraries...")

  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/Camera")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/ElementBuffer")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/Game")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/ImGUI")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/Practice")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/Shader")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/Texture2D")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/VertexArray")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core/Engine/VertexBuffer")
  add_subdirectory("${CMAKE_SOURCE_DIR}/src/Vendors/stb_image")
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

  target_link_libraries(GameExe PUBLIC spdlog::spdlog SDL2::SDL2 Game)
  target_link_libraries(Game PUBLIC spdlog::spdlog SDL2::SDL2 glad Practice)
  target_link_libraries(VertexBuffer PUBLIC glad)
  target_link_libraries(Shader PUBLIC glad)
  target_link_libraries(Practice PUBLIC SDL2::SDL2 glad)
  target_link_libraries(ElementBuffer PUBLIC glad)
  target_link_libraries(VertexArray PUBLIC glad)
  target_link_libraries(Texture2D PUBLIC stb_image glad spdlog::spdlog)
  target_link_libraries(Camera PUBLIC SDL2::SDL2 glad glm)
  target_link_libraries(ImGUI SDL2::SDL2 spdlog::spdlog glad)

  message(STATUS "All targets linked.")
endfunction()
