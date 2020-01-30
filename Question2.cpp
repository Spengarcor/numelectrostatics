#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <tuple>
#include "relax.h"
#include "Image.h"

using namespace std;



void save_to_csv(vector<vector<double>> mesh){

    ofstream csv_file;

    csv_file.open("Q2.csv");

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
    Image initialise(rows,cols);


    initialise.rectangle(0,0,rows,25,20);
    initialise.rectangle(0,cols-26,rows,26,-20);

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


    initialise.circle_alt(50,50,10, inner_circle_params, inner_circle_fix_dict);

    





    vector<vector<double>> example = initialise.get_mesh();
    vector<vector<bool>> c_grid = initialise.get_change_indices();

    Relax output(example,c_grid);



    output.relaxPotential(0.5, 0.00001, 1000000);

    example = output.get_mesh();

    save_to_csv(example);

    return 0;

}