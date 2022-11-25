#include "units.h"

void Unit::init(int x, int z) {
	posX = x;
	posZ = z;
}

unsigned int Unit::makeCube()
{

	//glEnable(GL_VERTEX_ARRAY);
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto vss = vertexShaderSourceCube.c_str();
	auto fss = fragmentShaderSourceCube.c_str();
	glShaderSource(vertexShader, 1, &vss, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fss, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	float vertices[] = {
	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 

	-0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 

	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 

	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 

	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f, -0.5f, 

	-0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f,
	};

	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);


	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	return 0;
}

void Unit::drawCube(std::string color) {

	//COLOR
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

	GLfloat blueColor[] = {
		0.0f, 0.0f, 1.0f,
	};//Blue
	GLfloat redColor[] = {
		1.0f, 0.0f, 0.0f,
	};//Red
	GLfloat greenColor[] = {
	0.0f, 1.0f, 0.0f
	};//Green
	GLfloat yellowColor[] = {
		1.0f, 1.0f, 0.0f
	};//Yellow


	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	if(color == "blue")
		glUniform4fv(vertexColorLocation, 1, blueColor);
	if(color == "red")
		glUniform4fv(vertexColorLocation, 1, redColor);
	if (color == "green")
		glUniform4fv(vertexColorLocation, 1, greenColor);
	if (color == "yellow") {
		glUniform4fv(vertexColorLocation, 1, yellowColor);
	}

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}




