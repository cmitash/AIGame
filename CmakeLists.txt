cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(ChecknGo)
include_directories(
  include/
)
add_executable( ChecknGo src/main.cpp src/state.cpp src/AI_minmax.cpp src/game.cpp)