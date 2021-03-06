#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "modified_eBS.h"

using namespace std;


int main(){

    int rows = 100, cols = 100;

    eBoundarySolver Q1_J(rows, cols);
    Q1_J.circle(50,50,45,nan(""),1.5,1.5);
    Q1_J.circle(50,50,25,0,0,nan(""));
    Q1_J.relaxPotential_J(10e-10, 100000);
    Q1_J.save_to_csv("Q1_J");

    eBoundarySolver Q1_GS(rows, cols);
    Q1_GS.circle(50,50,45,nan(""),1.5,1.5);
    Q1_GS.circle(50,50,25,0,0,nan(""));
    Q1_GS.relaxPotential_GS(10e-10, 100000);
    Q1_GS.save_to_csv("Q1_GS");

    eBoundarySolver Q1_SOR(rows, cols);
    Q1_SOR.circle(50,50,45,nan(""),1.5,1.5);
    Q1_SOR.circle(50,50,25,0,0,nan(""));
    Q1_SOR.relaxPotential_SOR(10e-10, 100000);
    Q1_SOR.save_to_csv("Q1_SOR");
    return 0;
}
