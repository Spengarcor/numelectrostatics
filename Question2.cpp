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

    int rows = 100, cols = 100;

    eBoundarySolver Q2(rows,cols);


    Q2.rectangle(0,0,rows,25,20);
    Q2.rectangle(0,cols-26,rows,26,-20);

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

    Q2.circle(50,50,10, inner_circle_params, inner_circle_fix_dict);


    Q2.relaxPotential_SOR(10e-5, 1000000);

    Q2.save_to_csv("Q2");

    return 0;

}