cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
  Source/Main.c
  Source/Display.c
  Source/Hooks.c)
target_link_libraries(main tcod raylib)
target_include_directories(main PUBLIC Source)
