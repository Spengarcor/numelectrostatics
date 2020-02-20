#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "eBoundarySolver.h"

using namespace std;


int main(){

    int rows = 100, cols = 100;

    eBoundarySolver Q1(rows, cols);

    //Set parameters for circle method
    map<string,double> outer_circle_params ={
        {"INSIDE", 0},
        {"BOUNDARY", 1.5},
        {"OUTSIDE", 1.5}
    };

    map<string,bool> outer_circle_fix_dict = {
        {"INSIDE", false},
        {"BOUNDARY", true},
        {"OUTSIDE", true}
    };

    Q1.circle(50,50,45, outer_circle_params, outer_circle_fix_dict);


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

    Q1.circle(50,50,25, inner_circle_params, inner_circle_fix_dict);


    Q1.relaxPotential_SOR(10e-10, 100000);

    Q1.save_to_csv("Q1");

    return 0;
}
