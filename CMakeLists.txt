cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS "-g -Wall -std=gnu11 -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_library(util SHARED
  Source/Util/Array.c
  Source/Util/Color.c
  )
target_include_directories(util PUBLIC Source/Util)

add_library(raytracer SHARED
  Source/Raytracer/Math.c
  Source/Raytracer/Scene.c
  Source/Raytracer/Raytracer.c
  Source/Raytracer/Viewport.c
  Source/Raytracer/Hooks.c
  )
target_include_directories(raytracer PUBLIC Source/Raytracer)
target_link_libraries(raytracer PUBLIC renderer util)

add_executable(main
  Source/Config.c
  Source/Main.c
  Source/Hooks.c)
target_include_directories(main PUBLIC Source)
target_link_libraries(main raytracer)
