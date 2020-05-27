//
// Created by Hamza Super PC on 5/27/2020.
//

#include "Linden.h"

Linden::Linden()
{
    iterations = 1;
}

Linden::Linden(int iterate)
{
    iterations = iterate;
}

Linden::Linden(int iterate, int varCount)
{
    if(varCount>25)
        throw "TOO MANY VARIABLES";

    iterations = iterate;

    for(int i=1; i <= varCount; i++)
    {
        variables.push_back(itol(i));
        variables.
    }
}

int Linden::getIterations()
{
    return iterations;
}

char

char Linden::itol(int n)
{
    assert(n >= 1 && n <= 26)
    return "abcdefghijklmnopqrstuvwxyz"[n-1];
}

