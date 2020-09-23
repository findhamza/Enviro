#pragma once
#ifndef THESUN_H

#include "syslib.h"

class TheSun
{
	coordPair focus;
	coordPair rim[128];
	float radius = 0.08;
	float sunVertices[387]; //size = ( size(rim) * 3 ) + 3
	int sunIndices[129];  //size = size(sunVertices) / 3

	coordPair worldFocus = { 0.0, -1.0 };
	
public:
	TheSun();
	void generateRim();
	void generateSunVertices();
	void generateSunIndices();
	float* getSunVertices();
	int* getSunIndices();

};

#endif // !THESUN_H

