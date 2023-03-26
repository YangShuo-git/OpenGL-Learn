include_directories(../3rdpart/glfw/include)
include_directories(../3rdpart/glad/include)

link_directories(../3rdpart/glfw/lib)

add_library(
	GL

	"../3rdpart/glad/src/glad.c"

	"gl.h"
	"gl_program.cpp"
	"gl_shader.cpp"
 "gl_vao.cpp")