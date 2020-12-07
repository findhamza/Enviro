#pragma once
#ifndef DEFAULT_H
#define DEFAULT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <string>
#include <ctype.h>
#include <ctime>
#include <Windows.h>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stack>
#include <thread>

struct plant {
	bool grow = false;
	bool wilt = false;
};

struct cloud {
	bool grow = false;
	bool rain = false;
};

struct updateFlag {
	struct plant plant;
	struct cloud cloud;
};

#endif