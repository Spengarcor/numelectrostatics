#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "eBoundarySolver.h"
using namespace std;


int main(){


        int rows = 500, cols = 500;

        eBoundarySolver Q1(rows, cols);

        //Set parameters for circle method
        map<string,double> outer_circle_params ={
            {"INSIDE", 0},
            {"BOUNDARY", 10},
            {"OUTSIDE", 10}
        };

        map<string,bool> outer_circle_fix_dict = {
            {"INSIDE", false},
            {"BOUNDARY", true},
            {"OUTSIDE", true}
        };

        Q1.circle(250,250,225, outer_circle_params, outer_circle_fix_dict);



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

        Q1.circle(250,250,50, inner_circle_params, inner_circle_fix_dict);
        

        Q1.relaxPotential_SOR(10e-5, 100000 , true);

        Q1.save_to_csv("100ver");



        vector<vector<double>> analytical_solution = Q1.analQ1(500,500,10,50,225,250,250);//PUT IN THINGS



        double err = Q1.get_abs_error(rows, cols, Q1.mesh, analytical_solution);

        //SAVE TO FILE

        cout << err;
        
    return 0;
}
