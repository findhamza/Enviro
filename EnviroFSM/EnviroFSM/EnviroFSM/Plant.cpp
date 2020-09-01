#include "Plant.h"

enum plantState_codes plantLookupTransition(plantState_codes plantCur, plantInputParam pInput)
{
    int table_size = sizeof plantState_transition / sizeof plantState_transition[0];
    for (int i = 0; i < table_size; i++)
        if (plantState_transition[i].plantSrc_state == plantCur 
            && plantState_transition[i].plantWater_codes == pInput.getWater 
            && plantState_transition[i].plantSun_codes == pInput.getSun)
            return plantState_transition[i].plantDst_state;
    return die;
}

plantInputParam pGenerateInput(bool wInput, bool sInput)
{
    struct plantInputParam inputInfo;
    inputInfo.getWater = (wInput) ? water : noWater;
    inputInfo.getSun = (sInput) ? sun : noSun;
    return inputInfo;
}

struct plantInputParam plantSeed_state(bool wInput, bool sInput)
{
    printf("\nPLANT SEEEDED");
    return pGenerateInput(wInput, sInput);
}

struct plantInputParam plantGrow_state(bool wInput, bool sInput)
{
    printf("\nPLANT GREW");
    return pGenerateInput(wInput, sInput);
}

struct plantInputParam plantSustain_state(bool wInput, bool sInput)
{
    printf("\nPLANT SUSTAINED");
    return pGenerateInput(wInput, sInput);
}

struct plantInputParam plantWilt_state(bool wInput, bool sInput)
{
    printf("\nPLANT WILTING");
    return pGenerateInput(wInput, sInput);
}

struct plantInputParam plantDie_state(bool wInput, bool sInput)
{
    printf("\nPLANT DIED :(");
    return pGenerateInput(wInput, sInput);
}
