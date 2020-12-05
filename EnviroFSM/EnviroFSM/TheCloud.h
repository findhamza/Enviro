#pragma once
#ifndef THECLOUD_H

#include "syslib.h"
#include "graphics.h"

class TheCloud
{
	struct rulePairs {
		std::string node;
		double chance;
		std::string nodePair;

		bool operator<(const rulePairs& a) const {
			return node < a.node;
		}
		bool operator==(const rulePairs& a) const {
			return node == a.node;
		}
	};

	struct cloudRules {
		int n;
		double angle;
		std::string seed;
		std::vector<rulePairs> rules;
		std::string structure;
		int growthPoint;
	};

	int cloudCount;
	cloudRules cloud;
	std::vector<coordPair> focus;
	float radius = 0.2;
	std::vector<Vertex> cloudVertex; //size = ( size(rim) * 6 ) + 6
	std::vector<unsigned int> cloudIndices;  //size = size(sunVertices) / 6
	std::vector<unsigned int> fullCloudIndices;
	int cloudIndCount=0;

	coordPair worldFocus = { 0.0, -1.0 };
	float worldRadius = 1.2;
	float speedConst = .01;
	float angularSpeed = .05;

	void getCloud(std::string cloudFile);
	void iterate();
	std::string findRule(char piece);
	std::string getCloud();
	void generateVU();
	void drawCloud();

public:
	TheCloud();
	std::vector<unsigned int>  updateCloud();
	void generateCloud();
	std::vector<Vertex> getCloudVertex();
	std::vector<unsigned int> getCloudIndices();

};

#endif // !THECLOUD_H

