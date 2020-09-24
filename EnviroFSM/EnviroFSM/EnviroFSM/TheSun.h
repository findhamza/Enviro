#pragma once
#ifndef THESUN_H

#include "syslib.h"

class TheSun
{
	coordPair focus;
	coordPair rim[2048];
	float radius = 0.1;
	float sunVertices[12294]; //size = ( size(rim) * 6 ) + 6
	int sunIndices[2049];  //size = size(sunVertices) / 6

	coordPair worldFocus = { 0.0, -1.0 };
	float speedConst = .01;
	
public:
	TheSun();
	void generateRim();
	void generateSunVertices();
	void generateSunIndices();
	void updateSun();
	std::vector<float> getSunVertices();
	std::vector<int> getSunIndices();

};

#endif // !THESUN_H

