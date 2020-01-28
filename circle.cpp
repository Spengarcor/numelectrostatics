#include <iostream>
#include <cmath>
#include <vector>
#include "circle.h"

using namespace std;



//Getters
vector<vector<double>> Grid::get_mesh(){

        return mesh;
    
}

vector<vector<bool>> Grid::get_change_indices(){

    return change_indices;

}

//constructor
Grid::Grid(int rows, int cols){

    vector<vector<double>> blank_mesh(rows, vector<double>(cols, 0));
    vector<vector<bool>> blank_change_indices(rows, vector<bool>(cols, true));

    mesh = blank_mesh;
    change_indices = blank_change_indices;

}



void Grid::circle(int centre_x, int centre_y, float radius, double IN_CIRCLE, 
        double BOUNDARY, double OUT_CIRCLE, bool IN_CIRCLE_FIX, bool BOUNDARY_FIX,
        bool OUT_CIRCLE_FIX){
  // getting the limits for the iteration
  int min_x{centre_x - (int(radius)+1)};

  int max_x{centre_x + (int(radius)+1)};

  int min_y{centre_y - (int(radius)+1)};

  int max_y{centre_y + (int(radius)+1)};

  
  for(int i=min_x;i<=max_x;i++){
    for(int j=min_y;j<=max_y;j++){
      float dist{(i-centre_x)*(i-centre_x) + (j-centre_y)*(j-centre_y)};
      
        // checking if a point is in the circle from the equation of a circle
        if(radius*radius>dist){
            if(IN_CIRCLE_FIX){
    	        mesh[i][j] = IN_CIRCLE; //CHANGE temp =10V for comparison
                change_indices[i][j] = true;
            }
        }
        else{
            if(OUT_CIRCLE_FIX){
                change_indices[i][j] = true;
            }
        }


        // So to avoid checking every point for a boundary
        if(fabs(sqrt(dist)-radius)<sqrt(2)){

	      // if the circle crosses a grid line within 0.5 from the point
	      if(fabs(sqrt(fabs(radius*radius-(centre_x-i)*(centre_x-1)))
	      	     -fabs(j-centre_y))
	         <=0.5 || 
	         fabs(sqrt(fabs(radius*radius-(centre_y-j)*(centre_y-j)))-
	      	fabs(i-centre_x))
	         <=0.5){
      	    mesh[i][j] = BOUNDARY;
            change_indices[i][j] = true;
	        }
        }
    }
 }

}