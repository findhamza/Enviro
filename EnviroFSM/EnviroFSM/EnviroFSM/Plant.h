#pragma once
#ifndef PLANT_H
#define PLANT_H

#include "syslib.h"
#pragma warning(disable : 26812)

int plantSeed_state(char*);
int plantGrow_state(char*);
int plantSustain_state(char*);
int plantWilt_state(char*);
int plantDie_state(char*);

static int (*plantState[])(char*) = { plantSeed_state, plantGrow_state, plantSustain_state, plantWilt_state, plantDie_state };
enum plantState_codes { seed, grow, sustain, wilt, die };
static const char* plantGet_State[] = { "seed", "grow", "sustain", "wilt", "die" };

enum plantRet_codes {water, sun, noWater, noSun};
static const char* plantGet_ret[] = { "water", "sun", "noWater", "noSun" };
struct plantTransition {
	enum plantState_codes plantSrc_state;
	enum plantRet_codes plantRet_codes;
	enum plantState_codes plantDst_state;
};

static struct plantTransition plantState_transition[] = {

	//seeded state transitions
	{seed,			water,			grow},
	{seed,			sun,			seed},
	{seed,			noWater,		seed},
	{seed,			noSun,			seed},

	//growth state transitions
	{grow,			water,			grow},
	{grow,			sun,			grow},
	{grow,			noWater,		sustain},
	{grow,			noSun,			sustain},

	//sustain state transitions
	{sustain,		water,			grow},
	{sustain,		sun,			grow},
	{sustain,		noWater,		wilt},
	{sustain,		noSun,			wilt},

	//wilt state transitions
	{wilt,		water,		sustain},
	{wilt,		sun,		sustain},
	{wilt,		noWater,	die},
	{wilt,		noSun,		die},

};

#define PLANT_EXIT die
#define PLANT_ENTRY seed

void plantManager(char*);
enum plantState_codes plantLookupTransition(plantState_codes, plantRet_codes);
enum plantRet_codes plantAssort(char*);

#endif