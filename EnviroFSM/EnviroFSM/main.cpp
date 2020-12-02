/* Author:		Hamza Syed			*/
/* COSC4050:	Indepenent Study	*/

#include "syslib.h"
#include "EnviroEngine.h"
#include "PlantObject.h"

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS; //originally it was 1000.0f
/*
bool randomBool() {
	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), rndEngine);
	return gen();
}
*/
int main(int argc, const char* argv[]) {
	printf("HELLO WORLD");

	int frameStart, frameTime;

	if (EnviroEngine::getInstance()->init("EnviroFSM", 100, 100, 480, 640, false/*false*/))
	{
		while (EnviroEngine::getInstance()->running())
		{
			frameStart = glfwGetTime();

			EnviroEngine::getInstance()->handleEvents();
			EnviroEngine::getInstance()->update((float) (glfwGetTime() - frameStart));
			EnviroEngine::getInstance()->render();

			frameTime = glfwGetTime() - frameStart;
			if (frameTime < DELAY_TIME)
			{
				Sleep((int)(DELAY_TIME - frameTime));
			}
		}
	}
	/*
	EnviroEngine::getInstance()->clean();

	PlantObject plantA;

	do {
		plantA.plantInput(randomBool(), randomBool(), 5);
		Sleep(100);
	} while (plantA.getTestState());
	*/
}