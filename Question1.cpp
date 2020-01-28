#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include "relax.h"
#include "circle.h"

using namespace std;



void save_to_csv(vector<vector<double>> mesh){

    ofstream csv_file;

    csv_file.open("for_np.csv");

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

    //use Grid object to draw shapes (initialise)
    Grid initialise(rows, cols);

    initialise.circle(50,50,10, 10,10,0, true,true,false);

    vector<vector<double>> grid = initialise.get_mesh();
    vector<vector<bool>> change_check = initialise.get_change_indices();

    save_to_csv(grid);
    







    //Relax solver(grid, change_check);

    //double bestp = solver.getBestp();


    //solver.relaxPotential(bestp, 0.01, 1000);






    return 0;
}




    // vector<vector<double>> grid(rows, vector<double>(cols));
    // vector<vector<bool>> change_check(rows, vector<bool>(cols, true)); 

    

    // //initialise array -> change to calling draw methods using draw object
    // for(int i = 0; i != rows; ++i){
    //     for(int j = 0; j != cols; ++j){
    //         //example 3.3 Griffiths

    //         if(j == 0){
                
    //             grid[i][j] = 10; //V0 = 10V
    //             change_check[i][j] = false;

    //         } else if(i == 0 || i == rows - 1){

    //             grid[i][j] = 0;
    //             change_check[i][j] = false;

    //         } else grid[i][j] = 0;


    //     }
    // }