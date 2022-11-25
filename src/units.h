#ifndef UNIT_H_
#define UNIT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders.h"

class Unit {

private:
	GLuint shaderProgram;
	unsigned int VAO;
public:
	unsigned int posX;
	unsigned int posZ;
	void init(int x, int z);
	GLuint getShaderProgram() { return shaderProgram; };
	unsigned int getVAO() { return VAO; };
	unsigned int makeCube();
	void drawCube(std::string color);
	int getx() { return posX; };
	int gety() { return posZ; };

};

#endif // UNIT_H_

