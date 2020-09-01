#pragma once
#ifndef PLANT_H
#define PLANT_H

#include "syslib.h"
#pragma warning(disable : 26812)

struct plantInputParam plantSeed_state(bool, bool);
struct plantInputParam plantGrow_state(bool, bool);
struct plantInputParam plantSustain_state(bool, bool);
struct plantInputParam plantWilt_state(bool, bool);
struct plantInputParam plantDie_state(bool, bool);

static struct plantInputParam (*plantState[])(bool, bool) = { plantSeed_state, plantGrow_state, plantSustain_state, plantWilt_state, plantDie_state };
enum plantState_codes { seed, grow, sustain, wilt, die };
static const char* plantGet_State[] = { "seed", "grow", "sustain", "wilt", "die" };

enum plantWater_codes {water, noWater};
static const char* plantWater_ret[] = { "water", "noWater" };
enum plantSun_codes {sun, noSun};
static const char* plantSun_ret[] = { "sun", "noSun" };
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

struct plantInputParam {
	enum plantWater_codes getWater;
	enum plantSun_codes getSun;
};

#define PLANT_EXIT die
#define PLANT_ENTRY seed

enum plantState_codes plantLookupTransition(plantState_codes, plantInputParam);
struct plantInputParam pGenerateInput(bool, bool);

#endif