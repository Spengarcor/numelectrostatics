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

    csv_file.open("Q3.csv");

    for(int i = 0; i != mesh.size(); ++i){
        for(int j = 0; j != mesh[0].size(); ++j){
    
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

    int rows = 300, cols = 300;

    //use Image object to draw shapes (initialise)
    Image initialise(rows,cols);


    initialise.rectangle(0,0,5,cols,0);
    initialise.rectangle(rows-6,0,5,cols,0);


    initialise.rectangle(150,30,45,60,0);
    initialise.rectangle(150,100,45,60,10);
    initialise.rectangle(150,170,45,60,-10);
    initialise.rectangle(150,240,45,60,0);


    vector<vector<double>> g = initialise.get_mesh();
    vector<vector<bool>> c = initialise.get_change_indices();


   
    Relax output(g,c);



    output.relaxPotential(0.5, 0.0001, 10000);

    vector<vector<double>> for_save = output.get_mesh();

    save_to_csv(for_save);

    return 0;

}