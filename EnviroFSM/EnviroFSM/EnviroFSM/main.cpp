/* Author:		Hamza Syed			*/
/* COSC4050:	Indepenent Study	*/

#include "syslib.h"
#include "EnviroEngine.h"
#include "PlantObject.h"

bool randomBool() {
	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), rndEngine);
	return gen();
}

int main(int argc, const char* argv[]) {
	printf("HELLO WORLD");

	if (EnviroEngine::getInstance()->init("EnviroFSM", 100, 100, 640, 480, false))
	{
		while (EnviroEngine::getInstance()->running())
		{
			EnviroEngine::getInstance()->handleEvents();
			EnviroEngine::getInstance()->update();
			EnviroEngine::getInstance()->render();
		}
	}

	EnviroEngine::getInstance()->clean();

	PlantObject plantA;

	do {
		plantA.plantInput(randomBool(), randomBool(), 5);
		Sleep(100);
	} while (plantA.getTestState());
}