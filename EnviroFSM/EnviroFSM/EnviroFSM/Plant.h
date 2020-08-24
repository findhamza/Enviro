#pragma once
#ifndef PLANT_H
#define PLANT_H

#include "syslib.h"

enum plantRet_codes plantAssort(char);
int plantSeed_state(char);
int plantGrow_state(char);
int plantSustain_state(char);
int plantWilt_state(char);
int plantDie_state(char);

static int (*state[])(char) = { plantSeed_state, plantGrow_state, plantSustain_state, plantWilt_state, plantDie_state };
enum plantState_codes { seed, grow, sustain, wilt, die };
static const char* plantGet_State[] = { "seed", "grow", "sustain", "wilt", "die" };

enum plantRet_codes {water, sun, noWater, noSun};
static const char* plantGet_ret[] = { "water", "sun", "noWater", "noSun" };
struct plantTransition {
	enum plantState_codes plantSrc_state;
	enum plantRet_codes planRet_codes;
	enum plantState_codes plantDst_state;
};

static struct plantTransition plantState_transition[] = {

	//seeded state transitions
	{seed,		water,		grow},
	{seed,		sun,		seed},
	{seed,		noWater,	seed},
	{seed,		noSun,		seed},

	//growth state transitions
	

};


#endif