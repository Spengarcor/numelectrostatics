#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <string>
#include "relax.h"
#include <cstdint>
#include <limits.h>

using namespace std;


Relax::Relax(vector<vector<double>> drawn_mesh, vector<vector<bool>> change_check){

        mesh = drawn_mesh;
        change_indices = change_check;
}


//Getters
vector<vector<double>> Relax::get_mesh(){

        return mesh;
    
}






double Relax::relaxPotential(double p, double del, int max_iter){

     /*
        p - relaxation parameter
        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on hte number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = 2*del; //CHANGE BACK TO 2*del
    int iter_count =0;
    int rows = mesh.size(), cols = mesh[0].size();

    //Values needed for equations
    double p_minus1 = 1-p;
    double hx = 1 / (double)rows, hy = 1 / (double)cols;
    double alpha = pow(hx/hy, 2);



    while(change > del && iter_count < max_iter){

        //Initialise change as will keep a running total for each mesh point
        change = 0;

        //Loop over all points
        for(int i = 0; i != rows; ++i){ 
            for(int j = 0; j != cols; ++j){
            
                
                //Check if it is to be ignored or not before changing
                if(change_indices[i][j]){

                    //save original value for change calculation
                    double pot_orig = mesh[i][j];                


                    //Basic handling of non-boundary edges
                    //For edges, just take the current value so the average is slightly weighted towards its current value
                    double x_before = i == 0 ? mesh[i][j] : mesh[i-1][j];
                    double x_after = i == rows - 1 ? mesh[i][j] : mesh[i+1][j];
                    double y_before = j == 0 ? mesh[i][j] : mesh[i][j-1];
                    double y_after = j == cols - 1 ? mesh[i][j] : mesh[i][j+1]; 

                    double pot_average = 1/(2 *(1 + alpha) ) 
                        * ( x_before + x_after + alpha*(y_before + y_after) );

                    mesh[i][j] = p * mesh[i][j] + p_minus1 * pot_average;


                    double difference = mesh[i][j] - pot_orig;
                    change += difference * difference; // add difference squared
                }
            }
        }


        //get RMS of change
        change = sqrt( change / (rows*cols) );
        //keep track of number of tierations
        ++iter_count;
    }

    return change;

}


double Relax::getBestp(){

    double best_error = INT_MAX;
    double best_p = 0;

    vector<vector<double>> temp_copy = mesh;

    for(double p = 0.1; p <=2; p += 0.1){
        if(p > 1-0.001 && p < 1 +0.001) continue;
        double error = relaxPotential(p,INT_MIN,10);
        if(best_error > error){
            best_p = p;
            best_error = error;
        }
        mesh = temp_copy;
    }

    return best_p;

}

