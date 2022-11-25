#ifndef SELECTOR_H_
#define SELECTOR_H_


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders.h"
#include "board.h"

class Selector {
private:
	Board board;
	GLuint shaderProgramSelector;
	unsigned int VAO_Selector;
	unsigned int EBO_Selector;
public:
	float posX = 0.0f;
	float posY = 0.0f;
	GLuint getShaderProgram() { return shaderProgramSelector; };
	unsigned int getVAOSelector() { return VAO_Selector; };
	unsigned int getEBOSelector() { return EBO_Selector; };
	unsigned int makeSelector();
	void drawSelector();
	void moveTile(int key);

	
};

#endif // !SELECTOR_H_

