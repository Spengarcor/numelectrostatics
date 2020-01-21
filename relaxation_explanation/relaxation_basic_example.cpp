#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

void relax(vector<vector<double>>& grid, double p, double del, int max_iter){
    /*
        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on hte number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = 2*del;
    int iter_count =0;
    int rows = grid.size(), cols = grid[0].size();

    //Values needed for equations
    double p_minus1 = 1-p;
    double hx = 1 / (double)rows, hy = 1 / (double)cols;
    double alpha = pow(hx/hy, 2);



    while(change > del && iter_count < max_iter){

        //Initialise change as will keep a running total for each grid point
        change = 0;

        //Loop over all points -> for production will probably have
        //a lsit of points to iterate over
        for(int i = 1; i != rows-1; ++i){ //for the specific griffiths example start at 1 and end one before the end (also start at col 1)
            for(int j = 1; j != cols; ++j){
            
                //save original value for change calculation
                double pot_orig = grid[i][j];                

                
                //Basic handling of non-boundary edges
                //For edges, just take the current value so the average is slightly weighted towards its current value
                double x_before = i == 0 ? grid[i][j] : grid[i-1][j];
                double x_after = i == rows - 1 ? grid[i][j] : grid[i+1][j];
                double y_before = j == 0 ? grid[i][j] : grid[i][j-1];
                double y_after = j == cols - 1 ? grid[i][j] : grid[i][j+1]; 

                double pot_average = 1/(2 *(1 + alpha) ) 
                    * ( x_before + x_after + alpha*(y_before + y_after) );

                grid[i][j] = p * grid[i][j] + p_minus1 * pot_average;


                double difference = grid[i][j] - pot_orig;
                change += difference * difference; // add difference squared
            }
        }


        //get RMS of change
        change = sqrt( change / (rows*cols) );
        //keep track of number of tierations
        ++iter_count;
    }


    //Check for convergence
    if(iter_count == max_iter) cout << "Convergence not found for the desired accuracy after" << max_iter << " iterations" << endl;


    //For quick check print out whole matrix
    for(int i=0; i != rows; ++i){
        for(int j = 0; j != cols; ++j){
            cout << grid[i][j] << " ";

        }
        cout << endl;
    }
}






int main(){

    //Set size of grid
    int rows = 30, cols = 13;


    //Create some grid as an array of arrays
    vector<vector<double>> grid(rows, vector<double>(cols)); 

    //initialise array -> change to calling draw methods using draw object
    for(int i = 0; i != rows; ++i){
        for(int j = 0; j != cols; ++j){
            //example 3.3 Griffiths

            if(j == 0) grid[i][j] = 10; //V0 = 10V
            else if(i == 0 || i == rows - 1) grid[i][j] = 0;
            else grid[i][j] = 20;
        }
    }

    //choose value of p -> in practice loop over [0,2] in steps of 0.1
    //for 10 iterations to see which value of p is best i.e. min error
    int p = 0.5;

    //TODO add 


  

    relax(grid, p, 0.0001, 1000);


    return 0;
}