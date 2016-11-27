cmake_minimum_required (VERSION 3.7.0)
project (JibsInferno)

# Include the src directory
include_directories ("${PROJECT_SOURCE_DIR}/src")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Final Steps
set(SOURCES src/main.cpp src/Game.h src/Game.cpp)
add_executable (JibsInferno ${SOURCES})
