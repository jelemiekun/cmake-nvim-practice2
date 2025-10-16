cmake_minimum_required(VERSION 3.20)

project(CMakeExercise LANGUAGES CXX C)

# Append cmake/ on CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Configuration
message("-- Configuring CMake and CXX...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Variables
message("-- Setting up variables...")
set(EXE_NAME GameExe)
set(HELPER_INCLUSION_SUCCESS FALSE)
set(HELPER_FILE Helper)
set(PACKAGES_TO_FIND spdlog SDL2 glm)
set(PACKAGES_FOUND)

# Helpers
include(${HELPER_FILE} RESULT_VARIABLE HELPER_INCLUSION_SUCCESS)
if (NOT "${HELPER_INCLUSION_SUCCESS}" STREQUAL "NOTFOUND")
  message("-- Successfully loaded ${HELPER_FILE}")
else()
  message("-- Failed to load ${HELPER_FILE}")
endif()

# Packages
if (COMMAND find_packages)
  find_packages("${PACKAGES_TO_FIND}")
endif()

# Libraries
add_subdirectory(src/Core/Game)

# Executables
add_executable(${EXE_NAME} src/main.cpp)

if (COMMAND link_all)
  link_all()
endif()

# Practice
set(PRAC_INCLUSION_SUCCESS FALSE)
set(PRAC_FILE Prac)

include(${PRAC_FILE} OPTIONAL RESULT_VARIABLE PRAC_INCLUSION_SUCCESS)
if (NOT "${PRAC_INCLUSION_SUCCESS}" STREQUAL "NOTFOUND")
  message("-- Successfully loaded ${PRAC_FILE}")
else()
  message("-- Failed to load ${PRAC_FILE}")
endif()

if (COMMAND prac_prac)
  cmake_print_properties("${PRAC_FILE}")
  prac_prac()
endif()

if(COMMAND practice)
  #  practice()
endif()

# TODOS
