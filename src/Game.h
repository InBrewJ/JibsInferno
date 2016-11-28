/*
 * Game.h
 *
 * The main game class, pending any sort of plan
 *
 */

#include <iostream>
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
// Include GLEW - always before gl.h and glfw.h because magic
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <vector>

using namespace glm;
using namespace std;

class Game {
public:

	Game();

	int init();
	int play();
	GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

 private:
	GLFWwindow* window;
	
};
