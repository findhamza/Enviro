#pragma once
#ifndef PLANTFSM_H
#define PLANTFSM_H

#include "syslib.h"
#pragma warning(disable : 26812)

#define PLANT_EXIT die
#define PLANT_ENTRY seed

double pWater = 0;
double sunEnergy = 0;

enum plantState_codes { seed, grow, sustain, wilt, die };
static const char* plantGet_State[] = { "seed", "grow", "sustain", "wilt", "die" };

enum plantWater_codes { water, noWater };
static const char* plantWater_ret[] = { "water", "noWater" };
enum plantSun_codes { sun, noSun };
static const char* plantSun_ret[] = { "sun", "noSun" };

struct plantInputParam {
	enum plantWater_codes getWater;
	enum plantSun_codes getSun;
};

plantInputParam pGenerateInput(bool wInput, bool sInput)
{
	struct plantInputParam inputInfo;
	inputInfo.getWater = (wInput) ? water : noWater;
	inputInfo.getSun = (sInput) ? sun : noSun;
	//if (wInput)
	//	waterVolume += 2;
	//if (sInput)
	//	sunEnergy += 2;
	return inputInfo;
}


struct plantInputParam plantSeed_state(bool wInput, bool sInput)
{
	return pGenerateInput(wInput, sInput);
}
struct plantInputParam plantGrow_state(bool wInput, bool sInput)
{
	//sunEnergy -= 2;
	waterVolume -= 2;
	return pGenerateInput(wInput, sInput);
}
struct plantInputParam plantSustain_state(bool wInput, bool sInput)
{
	//sunEnergy--;
	waterVolume--;
	return pGenerateInput(wInput, sInput);
}
struct plantInputParam plantWilt_state(bool wInput, bool sInput)
{
	return pGenerateInput(wInput, sInput);
}
struct plantInputParam plantDie_state(bool wInput, bool sInput)
{
	return pGenerateInput(wInput, sInput);
}

static struct plantInputParam (*plantState[])(bool, bool) = {
	plantSeed_state, plantGrow_state, plantSustain_state,
	plantWilt_state, plantDie_state
};

struct plantTransition {
	enum plantState_codes plantSrc_state;
	enum plantWater_codes plantWater_codes;
	enum plantSun_codes plantSun_codes;
	enum plantState_codes plantDst_state;
};

static struct plantTransition plantState_transition[] = {

	//seeded state transitions
	{seed,			water,		sun,			grow},
	{seed,			water,		noSun,			grow},
	{seed,			noWater,	sun,			seed},
	{seed,			noWater,	noSun,			seed},

	//growth state transitions
	{grow,			water,		sun,			grow},
	{grow,			water,		noSun,			sustain},
	{grow,			noWater,	sun,			sustain},
	{grow,			noWater,	noSun,			sustain},

	//sustain state transitions
	{sustain,		water,		sun,			grow},
	{sustain,		water,		noSun,			sustain},
	{sustain,		noWater,	sun,			wilt},
	{sustain,		noWater,	noSun,			wilt},

	//wilt state transitions
	{wilt,			water,		sun,			sustain},
	{wilt,			water,		noSun,			sustain},
	{wilt,			noWater,	sun,			wilt},
	{wilt,			noWater,	noSun,			die},

	//die state transitions
	{die,			water,		sun,			die},
	{die,			water,		noSun,			die},
	{die,			noWater,	sun,			die},
	{die,			noWater,	noSun,			die},
};

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

enum plantState_codes curPlantState = seed;
enum plantState_codes oldPlantState;
struct plantInputParam plantParam;
struct plantInputParam(*plantStateFun)(bool, bool);

plantState_codes processPlant(bool wInput, bool sInput) {
	if(wInput)
		pWater += 100;
	plantStateFun = plantState[curPlantState];
	plantParam = plantStateFun(wInput, sInput);
	if (pWater > 101 && sInput)
		curPlantState = grow;
	oldPlantState = curPlantState;
	curPlantState = plantLookupTransition(curPlantState, plantParam);
	return oldPlantState;
}

#endif