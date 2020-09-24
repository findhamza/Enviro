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
	int counter = 1;

	for (int i = 0; i < (sizeof(rim) / sizeof(rim[0])); i++)
	{
		if (i % 3 == 0)
			sunIndices[i] = 0;
		else if ((i - 1) % 3 == 0)
			sunIndices[i] = counter++;
		else
			sunIndices[i] = counter;
	}/*
	sunIndices[0] = 0;
	sunIndices[1] = 1;
	sunIndices[2] = 2;

	sunIndices[3] = 0;
	sunIndices[4] = 2;
	sunIndices[5] = 3;

	sunIndices[6] = 0;
	sunIndices[7] = 3;
	sunIndices[8] = 4;*/
}

std::vector<float> TheSun::getSunVertices()
{
	std::vector<float> verts;
	verts.assign(sunVertices, sunVertices + sizeof(sunVertices) / sizeof(sunVertices[0]));
	return verts;
}

std::vector<int> TheSun::getSunIndices()
{
	std::vector<int> inds;
	inds.assign(sunIndices, sunIndices + sizeof(sunIndices) / sizeof(sunIndices[0]));
	return inds;
}
