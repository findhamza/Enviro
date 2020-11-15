#include "TheCloud.h"

TheCloud::TheCloud()
{
	cloudCount = 15;
}

void TheCloud::generateCloud()
{
	getCloud("cloudA.DAT");
	cloudCount = cloud.n;
	cloud.structure = cloud.seed;
	std::string newStructure;

	for (int i = 0; i < cloud.n; i++)
	{
		iterate();
		std::cout << getCloud() << std::endl;
	}
	drawCloud();
}

void TheCloud::getCloud(std::string cloudFile)
{
	std::fstream file;
	file.open(cloudFile.c_str());
	std::string word;
	std::string oldWord = "start";

	while (file >> word)
	{
		if (word.compare("n") == 0) {
			file >> word;
			cloud.n = std::stoi(word);
			continue;
		}
		else if (word.compare("angle") == 0) {
			file >> word;
			cloud.angle = std::stod(word);
			continue;
		}
		else if (word.compare("seed") == 0) {
			file >> word;
			cloud.seed = word;
			continue;
		}
		else if (word.size() == 1 && word.compare("n") != 0) {
			cloud.rules.push_back(rulePairs());
			std::string node = word;
			file >> word;
			double chance = std::stod(word);
			file >> word;
			std::string nodePair = word;
			rulePairs newRule = { node, chance, nodePair };
			cloud.rules.back() = newRule;
		}
	}
}

void TheCloud::iterate()
{
	std::string newTree;

	for (int i = 0; i < cloud.structure.size(); i++) {
		char piece = cloud.structure[i];
		if (!ispunct(piece))
			newTree += findRule(piece);
		else
			newTree += piece;
	}

	cloud.structure = newTree;
}
std::string TheCloud::findRule(char piece)
{
	std::string node(1, piece);
	std::vector<rulePairs>::iterator it;
	rulePairs cloudPiece = { node = node };

	it = std::find(cloud.rules.begin(), cloud.rules.end() - 1, cloudPiece);

	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), rndEngine);

	return it->nodePair;
}

std::string TheCloud::getCloud()
{
	return cloud.structure;
}

void TheCloud::generateVU()
{
	coordPair point;
	glm::vec3 cloud_vertex;
	Vertex tempVert;
	float angleConst = (std::_Pi * 24) / 2048;
	float curAngle = std::_Pi / 2;
	unsigned int counter = 1;

	int detail = 2048 / 6;

	for (int f = 0; f < focus.size(); f++)
	{
		for (int r = 0; r < detail; r++)
		{
			point = { float(cos(curAngle) * radius + focus[f].x), float(sin(curAngle) * radius + focus[f].y) };
			curAngle += angleConst;
			tempVert.Position = glm::vec3(point.x, point.y, 0);
			tempVert.Color = glm::vec3(0.8, 0.8, 0.8);
			cloudVertex.push_back(tempVert);

			if (r % 3 == 0)
				cloudIndices.push_back((f*detail)/3);
			else if ((r - 1) % 3 == 0)
				cloudIndices.push_back(counter++);
			else
				cloudIndices.push_back(counter);
		}
	}
}

void TheCloud::drawCloud()
{
	std::vector<coordPair> cloudCoord;
	std::stack<coordPair> coordStack;
	coordPair coord = { 0.0,0.5 };
	cloudCoord.push_back(coord);
	coordStack.push(coord);

	std::stack<double> cloudAngle;
	cloudAngle.push(270);
	double curAngle = cloudAngle.top();

	float step = radius;// .3;
	float stepDown = .8;

	std::string str = cloud.structure;
	for (char& c : str) {
		if (c == '[') {
			coordStack.push(coord);
			cloudAngle.push(curAngle);
			step *= stepDown;
		}
		else if (c == ']') {
			coordStack.pop();
			cloudAngle.pop();
			step /= stepDown;
		}
		else if (c == '+') {
			curAngle = cloudAngle.top() + cloud.angle;
		}
		else if (c == '-') {
			curAngle = cloudAngle.top() - cloud.angle;
		}
		else if (c == 'F') {
			coord = { (float)(cos(cloudAngle.top() * (std::_Pi / 180))) * step + coordStack.top().x
					, (float)(sin(cloudAngle.top() * (std::_Pi / 180))) * step + coordStack.top().y };
			cloudCoord.push_back(coord);
		}
		else if (c == 'X') {
			coord = { (float)(cos(cloudAngle.top() * (std::_Pi / 180))) * step + coordStack.top().x
					, (float)(sin(cloudAngle.top() * (std::_Pi / 180))) * step + coordStack.top().y };
			cloudCoord.push_back(coord);
		}
	}

	focus.swap(cloudCoord);
	generateVU();
}

std::vector<Vertex> TheCloud::getCloudVertex()
{
	return cloudVertex;
}

std::vector<unsigned int> TheCloud::getCloudIndices()
{
	return cloudIndices;
}