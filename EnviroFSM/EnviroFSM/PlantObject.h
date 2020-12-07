#pragma once
#ifndef PLANTOBJECT_H
#define PLANTOBJECT_H


#include "syslib.h"
#include "graphics.h"

class PlantObject
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

	struct plantRules {
		int n;
		double angle;
		std::string seed;
		std::vector<rulePairs> rules;
		std::string structure;
		int growthPoint;
	};

	plantRules plant;
	std::vector<float> plantVertices;
	std::vector<int> plantIndices;
	std::vector<Vertex> plantVertex;
	std::vector<unsigned int> uInds;

	void generatePlant();
	void getPlant(std::string);
	void iterate();
	std::string findRule(char);
	std::string getTree();
	std::vector<float> plantVert(std::vector<coordPair>);
	std::vector<int> plantInd(int);


	int genericCount = 0;

	public:
		PlantObject();
		void drawTree();
		std::vector<Vertex> getPlantVertex();
		std::vector<float> getPlantVertices();
		std::vector<unsigned int> getPlantUIndices();
		std::vector<int> getPlantIndices();
		std::vector<unsigned int> updateTreeInds(updateFlag uFlags);
};
float rndFloat();

#endif // !PLANTOBJECT_H