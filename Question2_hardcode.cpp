#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
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

    double high = 20; // upper potential boundary
    double low = -20; // lower potential boundary
    int n = 41; // vector size
    int r = 6; // radius
  
    vector<vector<double>>  vec(n , vector<double> (n,0));
    vector<vector<bool>> change_check(n, vector<bool> (n,true));
  
    int mid = 0;
  
    if ( n % 2 == 0) // n is even, take point that is closest to middle, i.e n/2.
        mid = n/2;
    else // n is odd, so take midpoint to be exact middle since even number of values surround our point
        mid = (n-1)/2;
        
    //vec[mid][mid] = 0; Already 0
    change_check[mid][mid] = false;
    
    for(int i = mid - r; i <= mid + r; i++){ // looping over a square that contains the circle that will be generated, saves on computing time
        for(int j = mid - r; j <= mid + r; j++){
            if ((i-mid)*(i-mid) + (j-mid)*(j-mid) <= r*r){
                //vec[i][j] = 0; GROUNDD SPHERE SO 0V 
                change_check[i][j] = false;
            }
        }
    }
    
    for (int i=0; i<n;i++){ // populating the end boundaries
        vec[i][0]=high;
        change_check[i][0] = false;
        vec[i][n-1]=low;
        change_check[i][n-1] = false;
    }




    Relax solver(vec, change_check);

    //double bestp = solver.getBestp();


    solver.relaxPotential(0.5, 0.0005, 10000);



    vector<vector<double>> new_grid = solver.get_mesh();


    save_to_csv(new_grid);




    return 0;
}



