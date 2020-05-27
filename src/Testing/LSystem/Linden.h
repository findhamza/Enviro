//
// Created by Hamza Super PC on 5/27/2020.
//

#ifndef FSM_LINDEN_H
#define FSM_LINDEN_H

#include <iostream>
#include <vector>
#include <wsman.h>
#include <cstdlib>

class Linden {
    private:
        int iterations;
        std::vector<char> variables;

        char itol(int n);

    public:
        Linden();
        Linden(int iterate);
        Linden(int iterate, int varCount);

        int getIterations();

};


#endif //FSM_LINDEN_H
