#pragma once
#ifndef ENVIROENGINE_H
#define ENVIROENGINE_H

#include "syslib.h"
#include "graphics.h"
#include "Shader.h"
#include "Mesh.h"
#include "PlantObject.h"
#include "TheSun.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string getShader(std::string);
float randomFloat();
bool randomBool();

class EnviroEngine
{
	static EnviroEngine* instance;

	EnviroEngine() {

	}
	void setupObjects();

	GLFWwindow* window;
	Shader mainShader;
	std::string vertShader = getShader("shader.vert");
	std::string fragShader = getShader("shader.frag");
	const char* vShader = vertShader.c_str();
	const char* fShader = fragShader.c_str();

	PlantObject plantA;
	TheSun sun;
	Mesh plantObject, sunObject;

	int vertexShader;
	int success;
	char infoLog[512];
	int fragmentShader;
	int shaderProgram;
	int indicesCount;
	unsigned int VBO, VAO, EBO;


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