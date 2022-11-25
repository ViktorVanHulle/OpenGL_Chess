#ifndef GAME_H_
#define GAME_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders.h"


class Board {
private:
	GLuint shaderProgram;
	unsigned int VAO;
	unsigned int EBO_white;
	unsigned int EBO_black;
public: 
	GLuint getShaderProgram() { return shaderProgram; };
	unsigned int getVAO() { return VAO; };
	unsigned int getEBOWhite() { return EBO_black; };
	unsigned int getEBOBlack() { return EBO_white; };
	unsigned int makeBoard();
	void drawBoard();
};

#endif // GAME_H_

