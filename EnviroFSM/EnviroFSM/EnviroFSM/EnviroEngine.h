#pragma once
#ifndef ENVIROENGINE_H
#define ENVIROENGINE_H

#include "syslib.h"
#include "graphics.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string getShader(std::string);
float randomFloat();

class EnviroEngine
{
	static EnviroEngine* instance;

	EnviroEngine() {

	}

	GLFWwindow* window;
	std::string vertShader = getShader("shader.vert");
	std::string fragShader = getShader("shader.frag");
	const char* vShader = vertShader.c_str();
	const char* fShader = fragShader.c_str();
	/*const char* vShader = "#version 330 core\n"
							"layout (location = 0) in vec3 aPos;\n"
							"void main()\n"
							"{\n"
							"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
							"}\0";
	const char* fShader =	"#version 330 core\n"
							"out vec4 FragColor;\n"
							"void main()\n"
							"{\n"
							"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
							"}\n\0";*/


	int vertexShader;
	int success;
	char infoLog[512];
	int fragmentShader;
	int shaderProgram;
	unsigned int VBO, VAO, EBO;
	float xFloat = 0, yFloat = 0, rFloat = 0.5, thetaFloat = 0;


public:
	static EnviroEngine* getInstance() {
		if (!instance)
			instance = new EnviroEngine;
		return instance;
	}

	bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);

	bool running();

	void handleEvents();
	void update();
	void render();
	void clean();

	void quit();
};

#endif