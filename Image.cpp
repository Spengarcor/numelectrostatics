#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include "Image.h"

using namespace std;



//Getters
vector<vector<double>> Image::get_mesh(){

        return mesh;
    
}

vector<vector<bool>> Image::get_change_indices(){

    return change_indices;

}

//constructor
Image::Image(int rows, int cols){

    vector<vector<double>> blank_mesh(rows, vector<double>(cols, 0));
    vector<vector<bool>> blank_change_indices(rows, vector<bool>(cols, true));

    mesh = blank_mesh;
    change_indices = blank_change_indices;

}



void Image::circle(int centre_x, int centre_y, float radius, map<string,double> params, map<string,bool> fix_dict){
  // getting the limits for the iteration
  int min_x{centre_x - (int(radius)+1)};

  int max_x{centre_x + (int(radius)+1)};

  int min_y{centre_y - (int(radius)+1)};

  int max_y{centre_y + (int(radius)+1)};

  
  for(int i=min_x;i<=max_x;i++){
    for(int j=min_y;j<=max_y;j++){
      float dist{(i-centre_x)*(i-centre_x) + (j-centre_y)*(j-centre_y)};
      
        // checking if a point is in the circle from the equation of a circle
        if(radius*radius<dist){
            if(fix_dict["OUTSIDE"]){
    	        mesh[i][j] = params["OUTSIDE"]; 
                change_indices[i][j] = false; //if fixed then set changeable to false 
            }
        }
        else{
            if(fix_dict["INSIDE"]){
                mesh[i][j] = params["INSIDE"];
                change_indices[i][j] = false;
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
      	    mesh[i][j] = params["BOUNDARY"];
            change_indices[i][j] = false;
	        }
        }
    }
 }

}