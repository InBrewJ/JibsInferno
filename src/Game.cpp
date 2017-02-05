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
	width = 1024;
	height = 768;
	windowName = "Jib's Inferno";
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
	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open OpenGL window.\n");
		glfwTerminate();
		return -1;
			
	}
	
	glfwMakeContextCurrent(window);
	glewExperimental = true;

	return 0;
	
}

GLuint Game::LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
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

	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
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

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Projection matrix: 45 degree field of view, 16:9(?) ratio, display range:
	// 0.1 unit <-> 100 units

	mat4 Projection = perspective(radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);

	// Camera Matrix
	mat4 View = lookAt(
					   vec3(4,3,3), // Camera is a (0,0,-1) in world space
					   vec3(0,0,0), // and looks at the origin
					   vec3(0,1,0)  // Head is up (right hand rule)
					   );

	// Model matrix : an identity matrix (model will be at the origin)
	// and the thing to be played around with for scaling/rotating/translating etc

	// SCALE
	// ROTATE
	// TRANSLATE
	
	mat4 Model = mat4(1.0f);
	//vec3 myRotationAxis( 0, 0, 0);
	Model = translate(vec3(0.0f, 0.0f, 0.0f));
	//Model = rotate( Model, 0.0f, myRotationAxis );

	// Our ModelViewProjection : multiplication of our 3 matrices
	mat4 mvp = Projection * View * Model;

	// Create and compile our GLSL program from the programID

	GLuint programID = LoadShaders( "src/SimpleVertexShader.vertexshader.glsl",
									"src/SimpleFragmentShader.fragmentshader.glsl" );

	// Second step, give it to GLSL

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Color buffer
	GLuint colorbuffer;
	static GLfloat g_color_buffer_data[12*3*3];

	// And the do while loop

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Change the color of the vertices randomly as fuck
		// lots of casting here. Probably very slow? Who knows

		for (int v = 0; v < 12*3 ; v++){
			g_color_buffer_data[3*v+0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g_color_buffer_data[3*v+1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g_color_buffer_data[3*v+2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
						  1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
						  3,                                // size
						  GL_FLOAT,                         // type
						  GL_FALSE,                         // normalized?
						  0,                                // stride
						  (void*)0                          // array buffer offset
						  );

		
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
		
		// background dark blue
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f); 
		
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

		// Send our transformation to the correctly bound shader, in the "MVP"
		// uniform
		// This is done in the main loop since each model will have a different MVP matrix
		// (At least for the M part)

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		// Use our shader
		glUseProgram(programID);
		// Draw the triangle!
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
		glDisableVertexAttribArray(0);
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		

	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);

	return 0;
	
}
