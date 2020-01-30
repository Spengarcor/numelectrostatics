#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "relax.h"
#include "Image.h"

using namespace std;



void save_to_csv(vector<vector<double>> mesh){

    ofstream csv_file;

    csv_file.open("Q1.csv");

    for(int i = 0; i != mesh.size(); ++i){
        for(int j = 0; j != mesh.size(); ++j){
    
            csv_file << mesh[i][j];
            if(j != mesh.size()-1){
                csv_file << ";";
            }

        }
        csv_file << "\n";
    }

    csv_file.close();

}






int main(){



    int rows = 100, cols = 100;

    //use Image object to draw shapes (initialise)
    Image initialise(rows, cols);

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

    initialise.circle_alt(50,50,45, outer_circle_params, outer_circle_fix_dict);


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


    initialise.circle(50,50,25, inner_circle_params, inner_circle_fix_dict);


    //Retrieve mesh and bool mesh layer for pasing to relax object
    vector<vector<double>> grid = initialise.get_mesh();
    vector<vector<bool>> change_check = initialise.get_change_indices();


    Relax solver(grid, change_check);

    //double bestp = solver.getBestp();


    solver.relaxPotential(0.5, 0.001, 10000);


    vector<vector<double>> new_grid = solver.get_mesh();


    
    save_to_csv(new_grid);

    return 0;
}




