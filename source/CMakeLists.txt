cmake_minimum_required(VERSION 3.20)

project(practice LANGUAGES CXX C)

set(msg "Hello World!")

message("${msg}")

unset(msg)

set(x 10)
set(y 10)

math(EXPR z "${x} * ${y}")

message("${z}")

set(totoo TRUE)
set(hindi FALSE)

if (${totoo} OR ${hindi})
  message("Totoo ako!")
endif()

if(${totoo} AND (${z} GREATER 1))
  message("Aray ko!")
endif()

if (DEFINED meow)
  message("meow is defined!")
else()
  message("meow is undefined!")
endif()

if (EXISTS main.cpp)
  message("main.cpp exists!")
else()
  message("main.cpp does not exist!")
endif()

add_subdirectory(game)

if (TARGET s_Game)
  message("s_Game is defined")
else()
  message("s_Game not defined")
endif()
