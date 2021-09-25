cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS "-g -Wall -std=gnu11 -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_library(chip8 SHARED
  Source/Chip8/Chip8.c
  )
target_include_directories(chip8 PUBLIC Source/Chip8)

add_library(renderer SHARED
  Source/Renderer/Display.c
  )
target_include_directories(chip8 PUBLIC Source/Renderer)

add_executable(main
  Source/Main.c
  Source/Hooks.c)
target_link_libraries(main raylib chip8 renderer)
target_include_directories(main PUBLIC Source)
