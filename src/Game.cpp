/*
 * Game.cpp
 * 
 * The main game implementation class, also 
 * pending any sort of plan
 *
 */

#include "Game.h"

Game::Game() {
	cout << "Game constructor called" << endl;
	init();
}

int Game::init() {

	if (!glfwInit()) {
		fprintf(stderr, "Failed to init GLFW\n");
		return -1;
	}

	// All the glfw window stuff
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want old openGL

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Jib's Inferno", NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open OpenGL window.\n");
		glfwTerminate();
		return -1;
			
	}
	
	glfwMakeContextCurrent(window);
	glewExperimental = true;


	
	
}

// This is where the gameloop goes right?
int Game::play() {

	printf("Inside play\n");

	printf("Before glew init\n");

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "GLEW not okay boss.\n");
		return -1;
	}

	// Create vertex array object (VAO)

	GLuint VertexArrayID;
	printf("After GLuint\n");
	glGenVertexArrays(1, &VertexArrayID);
	printf("After gen vertex array\n");
	glBindVertexArray(VertexArrayID);

	printf("After bind vertex array\n");

	// An array of 3 vectors which represents 3 vertices

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// This will identify out vertex buffer
	GLuint vertexbuffer;
	
	// Generate 1 buffer, put the resulting identifier in vertexBuffer
	glGenBuffers(1, &vertexbuffer);

	printf("After genbuffers\n");

	// The following commands will talk about our "vertexBuffer" buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// The above only needs to be done once

		// And the do while loop

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// 1st attribute buffer : vertices

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
							  0,        // attribute 0, no particular reason for this but must match the layout in the shader
							  3,        // size
							  GL_FLOAT, // type
							  GL_FALSE, // normalized?
							  0,        // stride
							  (void*)0  // array buffer offset
							  );

		// Draw the triangle!
		glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0, 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		

	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);

	return 0;
	
}
