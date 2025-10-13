cmake_minimum_required(VERSION 3.20)

project(practice LANGUAGES CXX C)

set(msg "Hello World!")
set(x 5)
set(y 10)

math(EXPR z "(${x} + ${y}) / 5")

message(${msg})
message("(${x} + ${y}) / 5 = ${z}")

set()

if (${z})
