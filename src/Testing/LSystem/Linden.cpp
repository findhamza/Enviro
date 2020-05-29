//
// Created by Hamza Super PC on 5/27/2020.
//

#include "Linden.h"

Linden::Linden() {
    iterations = 1;
}

Linden::Linden(std::string treeFile) {
    std::ifstream t(treeFile);
    std::string str;

    //Read File To String
    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    std::cout << str << std::endl;

    //Split String Into Vector Token
    std::istringstream iss(str);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());

    std::reverse(results.begin(),results.end());
/*
    while(!results.empty()) {

        std::string strTmp = results.back();
        switch (strTmp.at(0)) {

            case 'n':
                results.pop_back();
                results.pop_back();
                strTmp = results.back();
                std::cout << strTmp << std::endl;
                results.pop_back();
                break;

            case 'a':
                results.pop_back();
                results.pop_back();
                strTmp = results.back();
                std::cout << strTmp << std::endl;
                results.pop_back();
                break;

        }
    }
    */
}

int Linden::getIterations() {
    return iterations;
}

char Linden::itol(int n) {
    assert(n >= 1 && n <= 26);
    return "abcdefghijklmnopqrstuvwxyz"[n-1];
}