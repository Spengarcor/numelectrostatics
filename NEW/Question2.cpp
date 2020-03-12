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

    ofstream myfile;
    myfile.open ("csv_data2.txt");

    for (int i=1; i<10; i++){
    
        int rows = 50*i, cols = 50*i;

        eBoundarySolver Q2(rows,cols);


        Q2.rectangle(0,0,rows,i,20);
        Q2.rectangle(0,cols-i,rows,i,-20);

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

        Q2.circle(25*i,25*i,10*i, inner_circle_params, inner_circle_fix_dict);

        Q2.relaxPotential_SOR(10e-5, 100000, false);


        Q2.save_to_csv("Q2_after_100k_GS");

        vector<vector<double>> analytical_solution = Q2.analQ2(rows,cols,20, 10*i,25*i,25*i, i,cols-i);

        double err = Q2.get_abs_error(rows, cols, Q2.mesh, analytical_solution);

        cout << err << "," << rows*cols << "," << "\n"; 
        myfile << err << "," << rows*cols << "," << "\n"; 
    }
    myfile.close();

    return 0;

}