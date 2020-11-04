#include "TheCloud.h"

TheCloud::TheCloud()
{
	cloudCount = 15;
}

void TheCloud::generateCloud()
{
	getCloud("cloudA.DAT");

	cloud.structure = cloud.seed;
	std::string newStructure;

	for (int i = 0; i < cloud.n; i++)
	{
		iterate();
		std::cout << getCloud() << std::endl;
	}
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

void TheCloud::generateRim()
{
	coordPair point;
	float angleConst = (std::_Pi * 24) / (sizeof(rim) / sizeof(rim[0]));
	float curAngle = std::_Pi / 2;

	for (int i = 0; i < (sizeof(rim) / sizeof(rim[0])); i++)
	{
		point = { float(cos(curAngle) * radius + focus.x), float(sin(curAngle) * radius + focus.y) };
		curAngle += angleConst;
		rim[i] = point;
	}
}

void TheCloud::drawCloud()
{
	std::vector<coordPair> cloudCoord;
	std::stack<coordPair> coordStack;
	coordPair coord = { 0.0,-1 };
	cloudCoord.push_back(coord);
	coordStack.push(coord);

	std::stack<double> cloudAngle;
	cloudAngle.push(90);
	double curAngle = cloudAngle.top();

	float step = .5;
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
}