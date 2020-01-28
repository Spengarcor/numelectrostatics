#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <string>
#include "relax.h"

using namespace std;




int main(){



    //use Grid object to draw shapes (initialise)


    

    int rows = 100, cols = 100;

    vector<vector<double>> grid(rows, vector<double>(cols));
    vector<vector<bool>> change_check(rows, vector<bool>(cols, true)); 

    

    //initialise array -> change to calling draw methods using draw object
    for(int i = 0; i != rows; ++i){
        for(int j = 0; j != cols; ++j){
            //example 3.3 Griffiths

            if(j == 0){
                
                grid[i][j] = 10; //V0 = 10V
                change_check[i][j] = false;

            } else if(i == 0 || i == rows - 1){

                grid[i][j] = 0;
                change_check[i][j] = false;

            } else grid[i][j] = 0;


        }
    }



    Relax solver(grid, change_check);

    double bestp = solver.getBestp();


    solver.relaxPotential(bestp, 0.01, 1000);






    return 0;
}
