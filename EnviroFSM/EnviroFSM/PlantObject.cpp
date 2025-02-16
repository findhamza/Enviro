#include "PlantObject.h"

PlantObject::PlantObject()
{
	generatePlant();
}
void PlantObject::generatePlant()
{
	getPlant("plantH.DAT");

	plant.structure = plant.seed;
	std::string newStructure;
	
	for (int i = 0; i < plant.n; i++)
	{
		//printf("\n");
		//std::cout << getTree() << std::endl;
		iterate();
		std::cout << getTree() << std::endl;
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

	//return it->nodePair;

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
}

std::string PlantObject::getTree() 
{
	return plant.structure;
}

void PlantObject::drawTree()
{
	std::vector<coordPair> plantCoord;
	std::stack<coordPair> coordStack;
	coordPair coord = { 0.0,-1 };
	plantCoord.push_back(coord);
	coordStack.push(coord);

	std::stack<double> plantAngle;
	plantAngle.push(90);
	double curAngle = plantAngle.top();

	float step = .38;
	float stepDown = .8;
	float angleStep = 1.04;

	std::string str = plant.structure;
	for (char& c : str) {
		if (c == '[') {
			coordStack.push(coord);
			plantAngle.push(curAngle);
			step *= stepDown;
			plant.angle *= angleStep;
		}
		else if (c == ']') {
			coordStack.pop();
			plantAngle.pop();
			step /= stepDown;
			plant.angle /= angleStep;
		}
		else if (c == '+') {
			//curAngle = std::fmod((plantAngle.top() + plant.angle), 180);
			curAngle = plantAngle.top() + plant.angle;
			//plantAngle.push(curAngle);
		}
		else if (c == '-') {
			//curAngle = std::fmod((plantAngle.top() - plant.angle), 180);
			curAngle = plantAngle.top() - plant.angle;
			//if (curAngle < 0)
				//curAngle *= -1;
			//plantAngle.push(curAngle);
		}
		else if (c == 'F') {
			coord = { (float)(cos(plantAngle.top() * (std::_Pi/180))) * step + coordStack.top().x
					, (float)(sin(plantAngle.top() * (std::_Pi / 180)))* step + coordStack.top().y };
			plantCoord.push_back(coord);
			//coordStack.push(coord);
			//std::cout << "x = " << plantCoord.back().x <<
				//", y = " << plantCoord.back().y <<
				//", angle = " << plantAngle.top() << std::endl;
		}
		else if (c == 'X') {
			coord = { (float)(cos(plantAngle.top() * (std::_Pi / 180))) * step + coordStack.top().x
					, (float)(sin(plantAngle.top() * (std::_Pi / 180))) * step + coordStack.top().y };
			plantCoord.push_back(coord);
			//coordStack.push(coord);
			//std::cout << "x = " << plantCoord.back().x <<
				//", y = " << plantCoord.back().y <<
				//", angle = " << plantAngle.top() << std::endl;
		}
	}

	plantVertices = plantVert(plantCoord);
	plantIndices = plantInd(plantVertices.size()/6);
	//std::pair<std::vector<float>, std::vector<int>> drawDetails;
	//drawDetails.first = plantVertices;
	//drawDetails.second = plantIndices;
}

std::vector<Vertex> PlantObject::getPlantVertex()
{
	Vertex vertex;
	glm::vec3 pos;
	glm::vec3 color;

	for(int i = 0; i < plantVertices.size()/6; i++) {
		pos = glm::vec3(plantVertices[i * 6], plantVertices[(i * 6) + 1], plantVertices[(i * 6) + 2]);
		color = glm::vec3(plantVertices[(i * 6) + 3], plantVertices[(i * 3) + 4], plantVertices[(i * 3) + 5]);
		vertex.Position = pos;
		vertex.Color = color;
		plantVertex.push_back(vertex);
	}

	return plantVertex;
}

std::vector<float> PlantObject::getPlantVertices()
{
	return plantVertices;
}

std::vector<unsigned int> PlantObject::getPlantUIndices()
{
	int ui;
	for (int i = 0; i < plantIndices.size(); i++)
	{
		ui = plantIndices[i];
		uInds.push_back(ui);
	}

	return uInds;
}

std::vector<int> PlantObject::getPlantIndices()
{
	return plantIndices;
}

std::vector<float> PlantObject::plantVert(std::vector<coordPair> plantCoord)
{
	std::vector<float> vert;
	float size = .005;

	//srand(time(NULL));
	float rnd = rndFloat();
	
	for (auto& point : plantCoord) {
		vert.push_back(point.x + size);
		vert.push_back(point.y - size);
		vert.push_back(0);
		vert.push_back(0.486);
		vert.push_back(0.298);
		vert.push_back(0.211);
		vert.push_back(point.x - size);
		vert.push_back(point.y - size);
		vert.push_back(0);
		vert.push_back(0.486);
		vert.push_back(0.298);
		vert.push_back(0.211);
		vert.push_back(rnd + point.x + size);
		vert.push_back(rnd + point.y + size);
		vert.push_back(0);
		vert.push_back(0.486);
		vert.push_back(0.298);
		vert.push_back(0.211);
		vert.push_back(rnd + point.x - size);
		vert.push_back(rnd + point.y + size);
		vert.push_back(0);
		vert.push_back(0.486);
		vert.push_back(0.298);
		vert.push_back(0.211);
	}

	return vert;
}

std::vector<int> PlantObject::plantInd(int count)
{
	std::vector<int> indicies;

	for (int i = 1; i <= count; i++) {
		if (i % 2 != 0) {
			indicies.push_back(i);
			indicies.push_back(i+1);
			indicies.push_back(i+3);
		}
		else {
			indicies.push_back(i-1);
			indicies.push_back(i+1);
			indicies.push_back(i+2);
		}
	}
	return indicies;
}

std::vector<unsigned int> PlantObject::updateTreeInds(updateFlag uFlags)
{
	if (uFlags.plant.grow) {
		genericCount += 3 * 20;
		genericCount %= uInds.size();
	}
	else if(uFlags.plant.wilt) {
		genericCount -= 3 * 20;
		if (genericCount < 0)
			genericCount = 3;
	}
	return std::vector<unsigned int>(uInds.begin(), uInds.begin() + genericCount);
}

float rndFloat() {
	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_real_distribution<>(0, .001), rndEngine);
	return gen();
}