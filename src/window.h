#ifndef WINDOW_H_
#define WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "board.h"
#include "Shaders.h"
#include "selector.h"
#include "units.h"
#include <vector>

class Window {
private:

public:
	float SC_WIDTH = 800.0f;
	float SC_HEIGHT = 800.0f;
	static Window& getInstance() // Singleton is accessed via getInstance()
	{
		static Window instance; // lazy singleton, instantiated on first use
		return instance;
	}

	GLFWwindow* window;
	Board board;
	Selector selector;
	std::vector<Unit> units1 = std::vector<Unit>(16);
	std::vector<Unit> units2 = std::vector<Unit>(16);
	Unit* selectedUnit;
	std::vector<int> selectedUnitPos= std::vector<int>(2, -1);
	bool enterPressed = false;

	float texRatio = 0.0f;
	float theta = 0.0f;
	float zoom = 0.0f;

	unsigned int windowCreator();
	unsigned int windowRun();
	void initTexture();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) // this method is specified as glfw callback
	{
		//here we access the instance via the singleton pattern and forward the callback to the instance method
		getInstance().keyButtonCallbackImpl(key, action);
	}

	void keyButtonCallbackImpl(int key, int action) //this is the actual implementation of the callback method
	{
		//the callback is handled in this instance method
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		{
			if (!enterPressed) {
				for (auto& unit : units1) {
					if (unit.posX == selector.posX * 8 && unit.posZ == abs(selector.posY * 8)) {
						selectedUnit = &unit;
						selectedUnitPos[0] = unit.posX;
						selectedUnitPos[1] = unit.posZ;
						enterPressed = true;
					}
				}
				for (auto& unit : units2) {
					if (unit.posX == selector.posX * 8 && unit.posZ == abs(selector.posY * 8)) {
						selectedUnit = &unit;
						selectedUnitPos[0] = unit.posX;
						selectedUnitPos[1] = unit.posZ;
						enterPressed = true;
					}
				}
			}
			else {
				bool placeTaken = false;
				enterPressed = false;

				for (auto& unit : units1) {
					if (unit.posX == selector.posX * 8 && unit.posZ == abs(selector.posY * 8)) {
						placeTaken = true;
					}
				}
				for (auto& unit : units2) {
					if (unit.posX == selector.posX * 8 && unit.posZ == abs(selector.posY * 8)) {
						placeTaken = true;
					}
				}
				if (!placeTaken) {
					selectedUnit->posX = abs(selector.posX * 8);
					selectedUnit->posZ = abs(selector.posY * 8);
				}		
				selectedUnit = nullptr;
				selectedUnitPos[0] = -1;
				selectedUnitPos[1] = -1;
			}
		}
		//the callback is handled in this instance method         

		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			selector.moveTile(GLFW_KEY_UP);
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			selector.moveTile(GLFW_KEY_DOWN);
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		{
			selector.moveTile(GLFW_KEY_LEFT);
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		{
			selector.moveTile(GLFW_KEY_RIGHT);
		}
		if (key == GLFW_KEY_T && action == GLFW_PRESS)
		{
			if (texRatio == 0.0f) {
				texRatio = 0.7f;
			}
			else
				texRatio = 0.0f;
		}
		if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
};

#endif // !1
