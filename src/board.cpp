#include "board.h"


unsigned int Board::makeBoard() {


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
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);


	//VERTEX & INDEX ARRAY
	float vertices[81 * 2];
	unsigned int indices_white[64 * 6];
	unsigned int indices_black[64 * 6];

	//length of cube
	float len = 1.0f / 8.0f;

	//array of vertices
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			vertices[(y * 9 + x) * 2] = -0.5f + len * x;
			vertices[(y * 9 + x) * 2 + 1] = 0.5f - len * y;
		}
	}

	//array of indices
	for (int r = 0; r < 8; r++) {
		for (int i = 0; i < 4; i++) {

			if (r % 2) {
				//WHITE SQUARE
				//upper triangle
				indices_white[(r * 8 + i) * 6] = r * 8 + r + (i * 2);
				indices_white[(r * 8 + i) * 6 + 1] = r * 8 + r + (i * 2) + 1;
				indices_white[(r * 8 + i) * 6 + 2] = r * 8 + r + (i * 2) + 10;
				//bottom triangle
				indices_white[(r * 8 + i) * 6 + 3] = r * 8 + r + (i * 2);
				indices_white[(r * 8 + i) * 6 + 4] = r * 8 + r + (i * 2) + 10;
				indices_white[(r * 8 + i) * 6 + 5] = r * 8 + r + (i * 2) + 9;

				///BLACK SQUARE
				//upper triangle
				indices_black[(r * 8 + i) * 6] = r * 8 + r + (i * 2) + 1;
				indices_black[(r * 8 + i) * 6 + 1] = r * 8 + r + (i * 2) + 2;
				indices_black[(r * 8 + i) * 6 + 2] = r * 8 + r + (i * 2) + 11;
				//bottom triangle
				indices_black[(r * 8 + i) * 6 + 3] = r * 8 + r + (i * 2) + 1;
				indices_black[(r * 8 + i) * 6 + 4] = r * 8 + r + (i * 2) + 11;
				indices_black[(r * 8 + i) * 6 + 5] = r * 8 + r + (i * 2) + 10;
			}
			else {
				//WHITE SQUARE
				//upper triangle
				indices_black[(r * 8 + i) * 6] = r * 8 + r + (i * 2);
				indices_black[(r * 8 + i) * 6 + 1] = r * 8 + r + (i * 2) + 1;
				indices_black[(r * 8 + i) * 6 + 2] = r * 8 + r + (i * 2) + 10;
				//bottom triangle
				indices_black[(r * 8 + i) * 6 + 3] = r * 8 + r + (i * 2);
				indices_black[(r * 8 + i) * 6 + 4] = r * 8 + r + (i * 2) + 10;
				indices_black[(r * 8 + i) * 6 + 5] = r * 8 + r + (i * 2) + 9;

				///BLACK SQUARE
				//upper triangle
				indices_white[(r * 8 + i) * 6] = r * 8 + r + (i * 2) + 1;
				indices_white[(r * 8 + i) * 6 + 1] = r * 8 + r + (i * 2) + 2;
				indices_white[(r * 8 + i) * 6 + 2] = r * 8 + r + (i * 2) + 11;
				//bottom triangle
				indices_white[(r * 8 + i) * 6 + 3] = r * 8 + r + (i * 2) + 1;
				indices_white[(r * 8 + i) * 6 + 4] = r * 8 + r + (i * 2) + 11;
				indices_white[(r * 8 + i) * 6 + 5] = r * 8 + r + (i * 2) + 10;
			}


		}

	}

	float vertices_texture[81 * 2];

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			vertices_texture[(i * 9 + j) * 2] = 0.0f + len * j;
			vertices_texture[(i * 9 + j) * 2 + 1] = 1.0f - len * i;
		}
	}


	unsigned int VBO, VBO_textures;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO_textures);


	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_texture), vertices_texture, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO_white);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_white), indices_white, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO_black);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_black), indices_black, GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_textures);


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);


	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	

	return 0;
}

void Board::drawBoard() {

	//COLOR
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	//UNIFORM
	//double timeValue = glfwGetTime();
	GLfloat blackColor[] = {
		0.0f, 0.0f, 0.0f, 1.0f
	};//Black
	GLfloat whiteColor[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};//White

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glUniform4fv(vertexColorLocation, 1, whiteColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glUniform4fv(vertexColorLocation, 1, blackColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

}


