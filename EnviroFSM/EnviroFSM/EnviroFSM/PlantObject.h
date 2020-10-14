#pragma once
#ifndef PLANTOBJECT_H
#define PLANTOBJECT_H


#include "syslib.h"
#include "graphics.h"
#include "Plant.h"

class PlantObject
{
	enum plantState_codes plantCurrent_State;
	enum plantState_codes plantOld_State;
	enum plantWater_codes plant_water;
	enum plantSun_codes plant_sun;
	struct plantInputParam(*plantState_fun)(bool, bool);

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

	void generatePlant();
	void getPlant(std::string);
	void iterate();
	std::string findRule(char);
	std::string getTree();
	std::vector<float> plantVert(std::vector<coordPair>);
	std::vector<int> plantInd(int);

	public:
		PlantObject();
		void plantInput(bool wInput, bool sInput, int potency);
		bool getTestState();
		void drawTree();
		std::vector<Vertex> getPlantVertex();
		std::vector<float> getPlantVertices();
		std::vector<unsigned int> getPlantUIndices();
		std::vector<int> getPlantIndices();
};
float rndFloat();

#endif // !PLANTOBJECT_H