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

    initialise.circle(50,50,25, 1,1,0, true,true,true);

    initialise.circle(50,50,45, 1,1,1, false,true,false);

    vector<vector<double>> grid = initialise.get_mesh();
    vector<vector<bool>> change_check = initialise.get_change_indices();

    







    Relax solver(grid, change_check);

    //double bestp = solver.getBestp();


    solver.relaxPotential(0.5, 0.001, 10000);


    vector<vector<double>> new_grid = solver.get_mesh();


    save_to_csv(new_grid);




    return 0;
}




