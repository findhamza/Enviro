#pragma once
#ifndef THESUN_H

#include "syslib.h"

class TheSun
{
	coordPair focus;
	coordPair rim[16];
	float radius = 0.5;
	float sunVertices[102]; //size = ( size(rim) * 6 ) + 6
	int sunIndices[17];  //size = size(sunVertices) / 6

	coordPair worldFocus = { 0.0, -1.0 };
	
public:
	TheSun();
	void generateRim();
	void generateSunVertices();
	void generateSunIndices();
	std::vector<float> getSunVertices();
	std::vector<int> getSunIndices();

};

#endif // !THESUN_H

