#pragma once
#ifndef CLOUDFSM_H
#define CLOUDFSM_H

#include "syslib.h"
#pragma warning(disable : 26812)

double rainChance = .2;
double waterVolume = 0;

enum cloudState_codes { cSeed, cGrowth, cSustain, cRain, cShrink };
static const char* cloudGet_State[] = { "cSeed", "cGrowth", "cSustain", "cRain", "cShrink" };

enum cloudSun_codes { cSun, cNoSun };
static const char* cloudSun_ret[] = { "cSun", "cNoSun" };

enum cloudSun_codes boolToSunCode(bool sun)
{
	return (sun) ? cSun : cNoSun;
}

enum cloudSun_codes cloudSeeded_state(bool sun)
{
	return boolToSunCode(sun);
}
enum cloudSun_codes cloudGrowth_state(bool sun)
{
	if (sun)
	{
		rainChance *= .99;
		waterVolume += 100;
	}
	return boolToSunCode(sun);
}
enum cloudSun_codes cloudSustain_state(bool sun)
{
	rainChance *= 1.1;
	return boolToSunCode(sun);
}
enum cloudSun_codes cloudRain_state(bool sun)
{
	rainChance *= 0.99;
	waterVolume -= 1;
	return boolToSunCode(sun);
}
enum cloudSun_codes cloudShrink_state(bool sun)
{
	if(sun)
		rainChance = 0.01;
	waterVolume -= 100;
	return boolToSunCode(sun);
}

static cloudSun_codes(*cloudState[])(bool) = { cloudSeeded_state, cloudGrowth_state, cloudSustain_state,
								cloudRain_state, cloudShrink_state };

struct cloudTransition {
	enum cloudState_codes cloudSrc_state;
	enum cloudSun_codes cloudSun_codes;
	enum cloudState_codes cloudDst_state;
};

static struct cloudTransition cloudState_transition[] = {
	{cSeed,			cSun,			cGrowth},
	{cSeed,			cNoSun,			cSustain},

	{cGrowth,		cSun,			cGrowth},
	{cGrowth,		cNoSun,			cSustain},

	{cSustain,		cSun,			cGrowth},
	{cSustain,		cNoSun,			cSustain},

	{cRain,			cSun,			cShrink},
	{cRain,			cNoSun,			cShrink},

	{cShrink,		cSun,			cGrowth},
	{cShrink,		cNoSun,			cSustain},
};

enum cloudState_codes cloudLookupTransition(cloudState_codes cloudCur, cloudSun_codes cloudSun)
{
	int table_size = sizeof cloudState_transition / sizeof cloudState_transition[0];
	for (int i = 0; i < table_size; i++)
		if (cloudState_transition[i].cloudSrc_state == cloudCur
			&& cloudState_transition[i].cloudSun_codes == cloudSun)
			return cloudState_transition[i].cloudDst_state;
	return cSustain;
}

enum cloudState_codes curCloudState = cSeed;
enum cloudState_codes oldCloudState;
enum cloudSun_codes cs;
enum cloudSun_codes(*cloudStateFun)(bool);

cloudState_codes processCloud(bool sun) {
	cloudStateFun = cloudState[curCloudState];
	cs = cloudStateFun(sun);
	if (rainChance > 0.89 && waterVolume > 700)
	{
		curCloudState = cRain;
	}
	oldCloudState = curCloudState;
	curCloudState = cloudLookupTransition(curCloudState, cs);

	//printf("%s-%lf ", cloudGet_State[oldCloudState], rainChance);
	return oldCloudState;
}
#endif