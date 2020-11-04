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
	std::vector<coordPair> rim[2048];
	float radius = 0.1;
	std::vector<float> sunVertices[4098]; //size = ( size(rim) * 6 ) + 6
	std::vector<unsigned int> sunIndices[683];  //size = size(sunVertices) / 6

	coordPair worldFocus = { 0.0, -1.0 };
	float worldRadius = 1.2;
	float speedConst = .01;
	float angularSpeed = .05;

	void getCloud(std::string cloudFile);
	void iterate();
	std::string findRule(char piece);
	std::string getCloud();

public:
	TheCloud();
	void generateCloud();
	void generateRim();
	void drawCloud();
	void generateCloudVertices();
	void generateCloudIndices();
	void updateCloud();
	std::vector<float> getCloudVertices();
	std::vector<Vertex> getCloudVertex();
	std::vector<unsigned int> getCloudIndices();

};

#endif // !THECLOUD_H

