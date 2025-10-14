cmake_minimum_required(VERSION 3.20)

project(CMakeExercise LANGUAGES CXX C)

message("-- Configuring CMake and CXX...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("-- Setting up variables...")
set(EXE_NAME GameExe)
set(HELPER_INCLUSION_SUCCESS FALSE)
set(HELPER_FILE Helper.cmake)
set(PACKAGES_TO_FIND spdlog SDL2 glm)
set(PACKAGES_FOUND)

include(${HELPER_FILE} RESULT_VARIABLE HELPER_INCLUSION_SUCCESS)
if (HELPER_INCLUSION_SUCCESS)
  message("-- Successfully loaded ${HELPER_FILE}")
else()
  message("-- Failed to load ${HELPER_FILE}")
endif()


if (COMMAND find_packages)
  find_packages("${PACKAGES_TO_FIND}")
endif()

add_executable(${EXE_NAME} src/main.cpp)

if (COMMAND link_all)
  link_all()
endif()







if (COMMAND prac)
  set(new_list P J N)
  prac("${new_list}")
endif()
