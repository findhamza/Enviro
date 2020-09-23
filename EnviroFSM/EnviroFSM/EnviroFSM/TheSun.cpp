#include "TheSun.h"

TheSun::TheSun()
{
	focus = { 0.0, 0.7 };
}

void TheSun::generateRim()
{
	coordPair point;
	float angleConst = (std::_Pi * 2) / (sizeof(rim) / sizeof(rim[0]));
	float curAngle = 0;
	
	for (int i = 0; i < (sizeof(rim) / sizeof(rim[0])); i++)
	{
		point = { cos(curAngle) * radius + focus.x, sin(curAngle) * radius + focus.y };
		curAngle += angleConst;

		rim[i] = point;
	}
}

void TheSun::generateSunVertices()
{
	//0.984, 0.894, 0.317 sun colors

	sunVertices[0] = focus.x;
	sunVertices[1] = focus.y;
	sunVertices[2] = 0;
	sunVertices[3] = 0.984;
	sunVertices[4] = 0.894;
	sunVertices[5] = 0.317;

	for (int i = 0; i < (sizeof(rim) / sizeof(rim[0])); i++)
	{
		sunVertices[((i + 1) * 6) + 0] = rim[i].x;
		sunVertices[((i + 1) * 6) + 1] = rim[i].y;
		sunVertices[((i + 1) * 6) + 2] = 0;
		sunVertices[((i + 1) * 6) + 3] = 0.984;
		sunVertices[((i + 1) * 6) + 4] = 0.894;
		sunVertices[((i + 1) * 6) + 5] = 0.317;
	}
}

void TheSun::generateSunIndices()
{
	for (int i = 0; i < (sizeof(rim) / sizeof(rim[0]))/3; i++)
	{
		sunIndices[i + 0] = (i * 3) + 1;
		sunIndices[i + 1] = (i * 3) + 2;
		sunIndices[i + 2] = 0;
	}
}

float* TheSun::getSunVertices()
{
	return sunVertices;
}

int* TheSun::getSunIndices()
{
	return sunIndices;
}
