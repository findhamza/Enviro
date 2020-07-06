//
// Created by Hamza Super PC on 5/27/2020.
//

#include "Linden.h"

Linden::Linden() {
    iterations = 2;
    angle = 26.7;
    tree = "F";

    TreeRules ruleOne = TreeRules {
            .variable = 'F',
            .probability = 1.0,
            .rules = "F[+F]C[-F]F"
    };

    TreeRules ruleTwo = TreeRules {
            .variable = 'C',
            .probability = 1.0,
            .rules = "C[+F]F[-C]F"
    };

    ruleSet.push_back(ruleOne);
    ruleSet.push_back(ruleTwo);

    std::sort(ruleSet.begin(), ruleSet.end());
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

}

int Linden::getIterations() {
    return iterations;
}

char Linden::itol(int n) {
    assert(n >= 1 && n <= 26);
    return "abcdefghijklmnopqrstuvwxyz"[n-1];
}

bool Linden::sortRules(const TreeRules &a, const TreeRules &b) {
    return a.variable < b.variable;
}

void Linden::iterate() {
    std::string newTree;

    for(int i=0; i<tree.size(); i++) {
        char piece = tree[i];
        newTree += findRule(piece);
    }

    tree = newTree;
    //char piece = tree.back(); tree.pop_back();
    //tree += findRule(piece);
}

std::string Linden::findRule(char piece) {
    std::vector<TreeRules>::iterator it;
    TreeRules treePiece = TreeRules {
        .variable = piece
    };

    it = std::find(ruleSet.begin(), ruleSet.end(), treePiece);

    std::mt19937 gen(time(NULL)+rand());
    std::uniform_real_distribution<> dis(0, 1);

    bool happens = dis(gen) <= it->probability;

    while(it != ruleSet.end() && !happens) {
        it = std::find(it, ruleSet.end(), treePiece);
        happens = dis(gen) <= it->probability;
        it = it.operator++();
    }

    if(it != ruleSet.end() && happens) {
        std::string rule = it->rules;
        return rule;
    }
    else
        return std::string(1, piece);
}

std::string Linden::getTree() {
    return tree;
}