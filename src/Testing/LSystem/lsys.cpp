//
// Created by Hamza Super PC on 5/26/2020.
//

#include "lsys.h"

int main() {

    std::cout << "Hello lsys " << std::endl;

    //std::string treeFile = "../DATA/TREE/TreeA.dat";
    //Linden A(treeFile);

    Linden treeA;
    for(int i=0; i<treeA.getIterations(); i++)
        treeA.iterate();
    std::cout << treeA.getTree() << std::endl;
}
