/* Author:		Hamza Syed			*/
/* COSC4050:	Indepenent Study	*/

#include "syslib.h"
#include "PlantObject.h"

int main(int argc, const char* argv[]) {
	printf("HELLO WORLD");

	std::string water = "water";
	std::string sun = "sun";
	std::string noWater = "noWater";
	std::string noSun = "noSun";
	char* sWater = &water[0];
	char* sSun = &sun[0];
	char* sNoWater = &noWater[0];
	char* sNoSun = &noSun[0];

	PlantObject plantA;

	srand((unsigned)time(0));
	for (int i = 0; i < 5; i++)
	{
		int state = 1 + (rand() % 4);
		printf("\n++%d++", state);
		switch (state)
		{
			case 1:
				plantA.plantInput(sWater);
			case 2:
				plantA.plantInput(sSun);
			case 3:
				plantA.plantInput(sNoWater);
			case 4:
				plantA.plantInput(sNoSun);
		}
		Sleep(10000);
	}
}