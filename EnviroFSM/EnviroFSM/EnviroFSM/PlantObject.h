#pragma once

#include "syslib.h"
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
		std::string nodePair;
	};

	struct plantRules {
		int n;
		int angle;
		std::vector<rulePairs> rules;
	};

	plantRules plant;

	void generatePlant();
	void getPlant(std::string);

	public:
		PlantObject();
		void plantInput(bool wInput, bool sInput, int potency);
		bool getTestState();
};

