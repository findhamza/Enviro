#pragma once
#ifndef THESUN_H

#include "syslib.h"
#include "graphics.h"

class TheSun
{
	coordPair focus;
	coordPair rim[2048];
	float radius = 0.4;
	float sunVertices[12294]; //size = ( size(rim) * 6 ) + 6
	int sunIndices[2049];  //size = size(sunVertices) / 6

	coordPair worldFocus = { 0.0, -1.0 };
	float worldRadius = 1.2;
	float speedConst = .01;
	float angularSpeed = .05;
	
public:
	TheSun();
	void generateRim();
	void generateSunVertices();
	void generateSunIndices();
	void updateSun();
	std::vector<float> getSunVertices();
	std::vector<Vertex> getSunVertex();
	std::vector<int> getSunIndices();
	std::vector<unsigned int> getSunUIndices();

	glm::vec4 getSkyColor();

};

#endif // !THESUN_H

