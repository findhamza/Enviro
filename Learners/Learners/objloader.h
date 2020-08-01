#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

#define _CRT_SECURE_NO_WARNINGS
class objloader
{
private:
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::vector < glm::vec3 > out_vertices;
	std::vector < glm::vec2 > out_uvs;
	std::vector < glm::vec3 > out_normals;

	std::string src;
	FILE* file;

	bool verifyFile();
	void setParam();
	void processParam();

public:
	objloader(std::string path);
	void draw();
	std::vector < glm::vec3 > getVertices();
	std::vector < glm::vec2 > getUvs();
	std::vector < glm::vec3 > getNormals();

};

#endif