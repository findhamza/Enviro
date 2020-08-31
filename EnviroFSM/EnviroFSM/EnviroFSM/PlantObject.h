#pragma once

#include "syslib.h"
#include "Plant.h"

class PlantObject
{
	enum plantState_codes plantCurrent_State;
	enum plantState_codes plantOld_State;
	enum plantRet_codes plant_rc;
	int(*plantState_fun)(char*);

	public:
		PlantObject();
		void plantInput(char*);

};

