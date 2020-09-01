#include "PlantObject.h"

PlantObject::PlantObject()
{
	plantCurrent_State = seed;
	plantOld_State = plantCurrent_State;
	generatePlant();
}

void PlantObject::plantInput(bool wInput, bool sInput, int potency)
{
	plantState_fun = plantState[plantCurrent_State];
	struct plantInputParam pInput = plantState_fun(wInput, sInput);
	
	plantOld_State = plantCurrent_State;
	plantCurrent_State = plantLookupTransition(plantCurrent_State, pInput);
}

bool PlantObject::getTestState()
{
	if (plantOld_State == die)
		return false;
	return true;
}


void PlantObject::generatePlant()
{
	getPlant("plantA.DAT");
}

void PlantObject::getPlant(std::string plantFile)
{
	std::fstream file;
	file.open(plantFile.c_str());
	std::string word;
	
	bool nFlag = false,
		angleFlag = false,
		seedFlag = false,
		ruleFlag = false;

	while (file >> word)
	{
		if (word == "n")
			while(file >> word)
	}
}
