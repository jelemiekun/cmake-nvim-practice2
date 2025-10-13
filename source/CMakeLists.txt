cmake_minimum_required(VERSION 3.20)

project(practice LANGUAGES CXX C)

set(msg "Hello World!")

message("${msg}")

unset(msg)

set(x 10)
set(y 10)

math(EXPR add "${x} / ${y}")

message("${z}")

set(totoo TRUE)
set(hindi FALSE)

if (${totoo} OR ${hindi})
  message("Totoo ako!")
else()
  message("Aray ko!")
endif()

