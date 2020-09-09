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

	if (plantOld_State == grow)
		plant.growthPoint += (int)(plant.structure.size() * .01);
	else if(plantOld_State == wilt)
		plant.growthPoint -= (int)(plant.structure.size() * .01);

	//std::cout << plant.growthPoint << "\n" << plant.structure.substr(0, plant.growthPoint) << std::endl;
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

	plant.structure = plant.seed;
	std::string newStructure;
	
	for (int i = 0; i < plant.n; i++)
	{
		//printf("\n");
		//std::cout << getTree() << std::endl;
		iterate();
		//std::cout << getTree() << std::endl;
	}
}

void PlantObject::getPlant(std::string plantFile)
{
	std::fstream file;
	file.open(plantFile.c_str());
	std::string word;
	std::string oldWord = "start";

	while (file >> word)
	{
		if (word.compare("n") == 0) {
			file >> word;
			plant.n = std::stoi(word);
			continue;
		}
		else if (word.compare("angle") == 0) {
			file >> word;
			plant.angle = std::stod(word);
			continue;
		}
		else if (word.compare("seed") == 0) {
			file >> word;
			plant.seed = word;
			continue;
		}
		else if (word.size() == 1 && word.compare("n") != 0) {
			plant.rules.push_back(rulePairs());
			std::string node = word;
			file >> word;
			double chance = std::stod(word);
			file >> word;
			std::string nodePair = word;
			rulePairs newRule = { node, chance, nodePair };
			plant.rules.back() = newRule;
		}
	}
}

void PlantObject::iterate() 
{
	std::string newTree;

	for (int i = 0; i < plant.structure.size(); i++) {
		char piece = plant.structure[i];
		if (!ispunct(piece))
			newTree += findRule(piece);
		else
			newTree += piece;
	}

	plant.structure = newTree;
}

std::string PlantObject::findRule(char piece) 
{
	std::string node(1, piece);
	std::vector<rulePairs>::iterator it;
	rulePairs treePiece = { node = node };

	it = std::find(plant.rules.begin(), plant.rules.end()-1, treePiece);

	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), rndEngine);

	return it->nodePair;

	/*
	bool happens = gen() <= it->chance;

	while (it != plant.rules.end() && !happens) {
		it = std::find(it, plant.rules.end(), treePiece);
		happens = gen() <= it->chance;
		it = it.operator++();
	}

	if (it != plant.rules.end() && happens) {
		std::string rule = it->nodePair;
		return rule;
	}
	else
		return std::string(1, piece);
	*/
}

std::string PlantObject::getTree() 
{
	return plant.structure;
}