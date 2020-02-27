#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <tuple>
#include "eBoundarySolver.h"

using namespace std;




int main(){

    int rows = 500, cols = 500;

    eBoundarySolver Q2(rows,cols);


    Q2.rectangle(0,0,rows,1,20);
    Q2.rectangle(0,cols-1,rows,1,-20);

    map<string,double> inner_circle_params ={
        {"INSIDE", 0},
        {"BOUNDARY", 0},
        {"OUTSIDE", 0}
    };

    map<string,bool> inner_circle_fix_dict = {
        {"INSIDE", true},
        {"BOUNDARY", true},
        {"OUTSIDE", false}
    };

    Q2.circle(250,250,60, inner_circle_params, inner_circle_fix_dict);


    Q2.relaxPotential_SOR(10e-10, 1000000);

    Q2.save_to_csv("Q2_SOR");

    return 0;

}