#include "PlantObject.h"

PlantObject::PlantObject()
{
	plantCurrent_State = seed;
	plantOld_State = plantCurrent_State;
}

void PlantObject::plantInput(char* pInput)
{
	printf("\n\n===%s", pInput);
	plantState_fun = plantState[plantCurrent_State];
	plant_rc = static_cast<plantRet_codes>(plantState_fun(pInput));
	
	plantOld_State = plantCurrent_State;
	plantCurrent_State = plantLookupTransition(plantCurrent_State, plant_rc);
}
