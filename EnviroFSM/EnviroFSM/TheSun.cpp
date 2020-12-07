#include "TheSun.h"

TheSun::TheSun()
{
	focus = { 0.0, .2 };
}

void TheSun::generateRim()
{
	coordPair point;
	float angleConst = (std::_Pi * 24) / (sizeof(rim) / sizeof(rim[0]));
	float curAngle = std::_Pi/2;
	
	for (int i = 0; i < (sizeof(rim) / sizeof(rim[0])); i++)
	{
		point = { float(cos(curAngle) * radius + focus.x), float(sin(curAngle) * radius + focus.y) };
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

	for (int i = 0; i < (sizeof(sunIndices) / sizeof(sunIndices[0])); i++)
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

void TheSun::updateSun()
{
	//focus.x += speedConst;
	//focus.y += speedConst;
	angularSpeed = fmod(angularSpeed+speedConst,std::_Pi*2);
	focus.x = worldFocus.x + cos(angularSpeed) * worldRadius;
	focus.y = worldFocus.y + sin(angularSpeed) * worldRadius;
	generateRim();
	generateSunVertices();
	generateSunIndices();
}

std::vector<float> TheSun::getSunVertices()
{
	std::vector<float> verts;
	verts.assign(sunVertices, sunVertices + sizeof(sunVertices) / sizeof(sunVertices[0]));
	return verts;
}

std::vector<Vertex> TheSun::getSunVertex()
{
	std::vector<Vertex> sunVertex;
	std::vector<float> sunVertices = getSunVertices();
	Vertex vertex;
	glm::vec3 pos;
	glm::vec3 color;

	for (int i = 0; i <  sunVertices.size()/ 6; i++) {
		pos = glm::vec3(sunVertices[i * 6], sunVertices[(i * 6) + 1], sunVertices[(i * 6) + 2]);
		color = glm::vec3(0.984, 0.894, 0.317);
		vertex.Position = pos;
		vertex.Color = color;
		sunVertex.push_back(vertex);
	}

	return sunVertex;
}

std::vector<int> TheSun::getSunIndices()
{
	std::vector<int> inds;
	inds.assign(sunIndices, sunIndices + sizeof(sunIndices) / sizeof(sunIndices[0]));
	return inds;
}

std::vector<unsigned int> TheSun::getSunUIndices()
{
	std::vector<unsigned int> uInds;
	std::vector<int> sunIndices = getSunIndices();
	int ui;
	for (int i = 0; i < sunIndices.size(); i++)
	{
		ui = sunIndices[i];
		uInds.push_back(ui);
	}

	return uInds;
}

glm::vec4 TheSun::getSkyColor()
{
	glm::vec4 color;
	float r = 0.2505 - std::sin((focus.y + 1) * (std::_Pi / 2.4)) * -0.2395;
	float g = 0.3895 - std::sin((focus.y + 1) * (std::_Pi / 2.4)) * -0.3625;
	float b = 0.5425 - std::sin((focus.y + 1) * (std::_Pi / 2.4)) * -0.4255;
	float a = 1.0f;
	color = glm::vec4(r, g, b, a);
	return color;
}

double TheSun::getSunPower()
{
	if (focus.y < 0)
		return (double)focus.y * (-1);
	else
		return 0;
}