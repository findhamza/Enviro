#pragma once
#ifndef ENVIROENGINE_H
#define ENVIROENGINE_H

#include "syslib.h"
#include "graphics.h"
#include "Shader.h"
#include "Mesh.h"
#include "PlantObject.h"
#include "TheSun.h"
#include "TheCloud.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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
	Shader sunShader;
	Shader cloudShader;
	std::string vertShader = getShader("shader.vert");
	std::string fragShader = getShader("shader.frag");
	const char* vShader = vertShader.c_str();
	const char* fShader = fragShader.c_str();

	PlantObject plantA;
	TheSun sun;
	TheCloud clouds;
	Mesh plantObject, sunObject, cloudObject;

	int vertexShader;
	int success;
	char infoLog[512];
	int fragmentShader;
	int shaderProgram;
	int indicesCount;
	unsigned int VBO, VAO, EBO;

	bool _fullscreen = false;
	void processInput(GLFWwindow* window);

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