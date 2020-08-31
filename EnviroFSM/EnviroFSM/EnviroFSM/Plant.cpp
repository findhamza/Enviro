#include "Plant.h"

void plantManager(char* plantInput)
{
    enum plantState_codes plantCur_state = seed;
    enum plantState_codes plantOld_state = plantCur_state;
    enum plantRet_codes plant_rc;
    int(*plantState_fun)(char*);

    for (;;)
    {
        plantState_fun = plantState[plantCur_state];
        plant_rc = static_cast<plantRet_codes>(plantState_fun(plantInput));
        if (PLANT_EXIT == plantCur_state)
            break;
        plantOld_state = plantCur_state;
        plantCur_state = plantLookupTransition(plantCur_state, plant_rc);
    }
}

enum plantState_codes plantLookupTransition(plantState_codes plantCur, plantRet_codes rc)
{
    int table_size = sizeof plantState_transition / sizeof plantState_transition[0];
    for (int i = 0; i < table_size; i++)
        if (plantState_transition[i].plantSrc_state == plantCur && plantState_transition[i].plantRet_codes == rc)
            return plantState_transition[i].plantDst_state;
    return die;
}

plantRet_codes plantAssort(char* plantInput)
{
    if (strcmp(plantInput, "water") == 0)
        return water;
    else if (strcmp(plantInput, "sun") == 0)
        return sun;
    else if (strcmp(plantInput, "noWater") == 0)
        return noWater;
    else if (strcmp(plantInput, "noSun") == 0)
        return noSun;
}

int plantSeed_state(char* plantInput)
{
    printf("\nPLANT SEEEDED");
    return plantAssort(plantInput);
}

int plantGrow_state(char* plantInput)
{
    printf("\nPLANT GREW");
    return plantAssort(plantInput);
}

int plantSustain_state(char* plantInput)
{
    printf("\nPLANT SUSTAINED");
    return plantAssort(plantInput);
}

int plantWilt_state(char* plantInput)
{
    printf("\nPLANT WILTING");
    return plantAssort(plantInput);
}

int plantDie_state(char* plantInput)
{
    printf("\nPLANT DIED :(");
    return plantAssort(plantInput);
}
