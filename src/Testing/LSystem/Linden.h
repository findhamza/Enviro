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
#include <regex>
#include <time.h>
#include <random>

#define T_LEFT +
#define T_RIGHT -
#define T_AROUND |
#define DOWN &
#define UP ^
#define R_LEFT \
#define R_RIGHT /

struct TreeRules {
    char variable;
    float probability;
    std::string rules;

    bool operator<(const TreeRules &a) const {
        return variable < a.variable;
    }
    bool operator==(const TreeRules &a) const {
        return variable == a.variable;
    }
};

class Linden {

    private:
        //Private Variables
            int iterations;
            int angle;
            std::string tree;
            std::vector<TreeRules> ruleSet;
        //Private Functions
            char itol(int n);
            bool sortRules(const TreeRules&, const TreeRules&);

    public:
        //Constructors
            Linden();
            Linden(std::string);
        //Methods
            void iterate();
            int getIterations();
            std::string getTree();
            std::string findRule(char piece);

};


#endif //FSM_LINDEN_H
