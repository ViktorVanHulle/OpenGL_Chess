#include "window.h"
#include <stb_image.h>

unsigned int Window::windowCreator()
{
	window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "3D chess", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//Call the key callback method when there is keyboard input
	glfwSetKeyCallback(window, &Window::key_callback);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

unsigned int Window::windowRun()
{

	float offset = 1.0f / 8.0f;
	//Create chess board
	board.makeBoard();
	//Create Selector
	selector.makeSelector();
	//create texture
	initTexture();

	//---Coordinate systems---
	//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

	//view matrix - move view around the scene
	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
	//projection matrix - perspective
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SC_WIDTH / (float)SC_HEIGHT, 0.1f, 100.0f);



	//---Coordinate systems Cubes---
	//model matrix - translations, rotations, scaling
	//view matrix - move view around the scene
	glm::mat4 view_U = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	//view_U = glm::lookAt(
	//	glm::vec3(sin(theta), 10.0f, cos(theta)),
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f)
	//);
	//view_U = glm::translate(view_U, glm::vec3(1.0f, 1.0f, -10.0f));
	//projection matrix - perspective
	glm::mat4 projection_U = glm::perspective(glm::radians(45.0f), (float)SC_WIDTH / (float)SC_HEIGHT, 0.1f, 100.0f);


	//DRAW BLUE CUBES
	for (int r = 0; r < 2; r++) {
		for (int i = 0; i < 8; i++) {
			Unit unit;
			unit.makeCube();
			unit.init(i, r);
			units1.push_back(unit);
		}
	}

	//DRAW RED CUBES
	for (int r = 0; r < 2; r++) {
		for (int i = 0; i < 8; i++) {
			Unit unit;
			unit.makeCube();
			unit.init(i, 6 + r);
			units2.push_back(unit);
		}
	}

	
	while (!glfwWindowShouldClose(window))
	{
		//CHANGE CAMERA POSITION
		//rotate clock
		if (glfwGetKey(window, GLFW_KEY_L))
		{
			theta -= 0.005f;
		}
		//rotate counter clock
		if (glfwGetKey(window, GLFW_KEY_H))
		{
			theta += 0.005f;
		}
		//zoom in
		if (glfwGetKey(window, GLFW_KEY_P))
		{
			zoom -= 0.005f;
		}
		//zoom out
		if (glfwGetKey(window, GLFW_KEY_O))
		{
			zoom += 0.005f;
		}
		float zoomXZ = (15.0f / 10.0f * zoom);
		view = glm::lookAt(
			glm::vec3(sin(theta) * (15 + zoomXZ), 10.0f + zoom, cos(theta) * (15 + zoomXZ)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		view_U = glm::lookAt(
			glm::vec3(sin(theta) * (15 + zoomXZ), 10.0f + zoom, cos(theta) * (15 + zoomXZ)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		//Texture 
		glUseProgram(board.getShaderProgram());
		glUniform1f(glGetUniformLocation(board.getShaderProgram(), "texRatio"), texRatio);

		//bg color
		glClearColor(0.128f, 0.128f, 0.128f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(board.getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized



		//send matrices to shader (each frame)
		//send model matrix
		//model matrix - translations, rotations, scaling
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		int modelLoc = glGetUniformLocation(board.getShaderProgram(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//send view matrix
		int viewLoc = glGetUniformLocation(board.getShaderProgram(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//send projection matrix
		int projectionLoc = glGetUniformLocation(board.getShaderProgram(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//Draw chess board
		board.drawBoard();



		glUseProgram(selector.getShaderProgram());
		glBindVertexArray(selector.getVAOSelector()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		//send matrices to shader (each frame)
		//send model matrix
		int modelLoc_S = glGetUniformLocation(selector.getShaderProgram(), "model");
		glUniformMatrix4fv(modelLoc_S, 1, GL_FALSE, glm::value_ptr(model));
		//send view matrix
		int viewLoc_S = glGetUniformLocation(selector.getShaderProgram(), "view");
		glUniformMatrix4fv(viewLoc_S, 1, GL_FALSE, glm::value_ptr(view));
		//send projection matrix
		int projectionLoc_S = glGetUniformLocation(selector.getShaderProgram(), "projection");
		glUniformMatrix4fv(projectionLoc_S, 1, GL_FALSE, glm::value_ptr(projection));

		selector.drawSelector();





		//DRAW BLUE CUBES
		for (auto& unit : units1) {
			glUseProgram(unit.getShaderProgram());
			glBindVertexArray(unit.getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


			glm::mat4 model_U = glm::mat4(1.0f);
			int modelLoc_U = glGetUniformLocation(unit.getShaderProgram(), "model");
			model_U = glm::translate(model_U, glm::vec3(-3.5f + unit.getx(), 0.3f, -3.5f + unit.gety()));
			model_U = glm::scale(model_U, glm::vec3(0.6f, 0.6f, 0.6f));
			glUniformMatrix4fv(modelLoc_U, 1, GL_FALSE, glm::value_ptr(model_U));
			//send view matrix
			int viewLoc_U = glGetUniformLocation(unit.getShaderProgram(), "view");

			glUniformMatrix4fv(viewLoc_U, 1, GL_FALSE, glm::value_ptr(view_U));
			//send projection matrix
			int projectionLoc_U = glGetUniformLocation(unit.getShaderProgram(), "projection");
			glUniformMatrix4fv(projectionLoc_U, 1, GL_FALSE, glm::value_ptr(projection_U));
			glUniform1f(glGetUniformLocation(unit.getShaderProgram(), "texRatio"), texRatio);

			if (selectedUnitPos[0] == unit.getx() && selectedUnitPos[1] == unit.gety()) {
				unit.drawCube("yellow");
			}
			else if (unit.posX == selector.posX * 8 && unit.posZ == abs(selector.posY * 8)) {
				unit.drawCube("green");
			}
			else {
				unit.drawCube("blue");
			}

		}

		//DRAW RED CUBES
		for (auto& unit : units2) {
			glUseProgram(unit.getShaderProgram());
			glBindVertexArray(unit.getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


			glm::mat4 model_U = glm::mat4(1.0f);
			int modelLoc_U = glGetUniformLocation(unit.getShaderProgram(), "model");
			model_U = glm::translate(model_U, glm::vec3(-3.5f + unit.getx(), 0.3f, -3.5f + unit.gety()));
			model_U = glm::scale(model_U, glm::vec3(0.6f, 0.6f, 0.6f));
			glUniformMatrix4fv(modelLoc_U, 1, GL_FALSE, glm::value_ptr(model_U));
			//send view matrix
			int viewLoc_U = glGetUniformLocation(unit.getShaderProgram(), "view");

			glUniformMatrix4fv(viewLoc_U, 1, GL_FALSE, glm::value_ptr(view_U));
			//send projection matrix
			int projectionLoc_U = glGetUniformLocation(unit.getShaderProgram(), "projection");
			glUniformMatrix4fv(projectionLoc_U, 1, GL_FALSE, glm::value_ptr(projection_U));
			glUniform1f(glGetUniformLocation(unit.getShaderProgram(), "texRatio"), texRatio);

			if (selectedUnitPos[0] == unit.getx() && selectedUnitPos[1] == unit.gety()) {
				unit.drawCube("yellow");
			}
			else if (unit.posX == selector.posX * 8 && unit.posZ == abs(selector.posY * 8)) {
				unit.drawCube("green");
			}
			else {

				unit.drawCube("red");
			}

		}


		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	glfwTerminate();
	return 0;
}

void Window::initTexture() {


	int WIDTH, HEIGHT, COMP;

	//FLOOR TEXTURE
	std::string filepath = std::string(TEXTURE_DIR) + std::string("floor_texture.png");
	auto data = stbi_load(filepath.c_str(), &WIDTH, &HEIGHT, &COMP, STBI_rgb_alpha);
	if (!data) {
		std::cerr << "TEXTURE NOT LOADED" << std::endl;
	}

	// Generate the texture
	GLuint tex;
	glGenTextures(1, &tex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);


	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	//CUBE TEXTURE
	std::string filepath_cube = std::string(TEXTURE_DIR) + std::string("cube_texture.png");
	data = stbi_load(filepath_cube.c_str(), &WIDTH, &HEIGHT, &COMP, STBI_rgb_alpha);
	if (!data) {
		std::cerr << "TEXTURE NOT LOADED" << std::endl;
	}
	// generate the texture
	GLuint tex_cube;
	glGenTextures(1, &tex_cube);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);

	//Image to GPU
	for (unsigned int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8,
			WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}


	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);


	//param texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	stbi_image_free(data);
}

