//
// Created by Hamza Super PC on 5/27/2020.
//

#ifndef FSM_LINDEN_H
#define FSM_LINDEN_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <iterator>
#include <sstream>
#include <algorithm>

#define T_LEFT +
#define T_RIGHT -
#define T_AROUND |
#define DOWN &
#define UP ^
#define R_LEFT \
#define R_RIGHT /

class Linden {

    int iterations;
    int angle;
    std::string tree;
    std::vector<std::string> rules;

    char itol(int n);

    public:
        Linden();
        Linden(std::string);

        int getIterations();

};


#endif //FSM_LINDEN_H
