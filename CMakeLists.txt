cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(ChecknGo)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
  include/
  ${GLUT_INCLUDE_DIRS}
)

add_executable( ChecknGo src/main.cpp src/state.cpp src/AI_minmax.cpp src/game.cpp)
target_link_libraries(ChecknGo
	${OPENGL_LIBRARY}
	${GLUT_LIBRARY}
)