#include "selector.h"

unsigned int Selector::makeSelector() {
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto vss = vertexShaderSource.c_str();
	auto fss = fragmentShaderSource.c_str();
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
	shaderProgramSelector = glCreateProgram();
	glAttachShader(shaderProgramSelector, vertexShader);
	glAttachShader(shaderProgramSelector, fragmentShader);
	glLinkProgram(shaderProgramSelector);

	// check for linking errors
	glGetProgramiv(shaderProgramSelector, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramSelector, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	//VERTEX & INDEX ARRAY
	float vertices[] = {
		 -0.375f + posX,  0.5f + posY,  // top right
		 -0.375f + posX, 0.375f + posY,  // bottom right
		 -0.5f + posX, 0.375f + posY,  // bottom left
		 -0.5f + posX, 0.5f + posY,  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO;

	glGenVertexArrays(1, &VAO_Selector);
	glGenBuffers(1, &VBO);


	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_Selector);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO_Selector);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Selector);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);


	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	


	return 0;
}

void Selector::drawSelector() {
	//COLOR
	int vertexColorLocation = glGetUniformLocation(shaderProgramSelector, "ourColor");
	//UNIFORM
	GLfloat greenColor[] = {
		0.0f, 1.0f, 0.0f
	};//Green

	glUseProgram(shaderProgramSelector);
	glBindVertexArray(getVAOSelector());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getEBOSelector());
	glUniform4fv(vertexColorLocation, 1, greenColor);

	glDrawElements(GL_TRIANGLES, 4 * 3, GL_UNSIGNED_INT, 0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Selector::moveTile(int key)
{
	//length of cube
	float len = 1.0f / 8.0f;
	if (key == GLFW_KEY_UP) {
		if(posY+len < 0.125f)
			posY = posY + len;
	}
	if (key == GLFW_KEY_DOWN) {
		if (posY - len > -1.0f)
			posY = posY - len;
	}
	if (key == GLFW_KEY_LEFT) {
		if (posX - len > -0.125f)
			posX = posX - len;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (posX + len < 1.0f)
			posX = posX + len;
	}

	makeSelector();
}