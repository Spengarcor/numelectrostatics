#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <tuple>
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
Image::Image(int rows_in, int cols_in){

    vector<vector<double>> blank_mesh(rows, vector<double>(cols, 0));
    vector<vector<bool>> blank_change_indices(rows, vector<bool>(cols, true));

    mesh = blank_mesh;
    rows = rows_in; cols = cols_in;

    change_indices = blank_change_indices;

}

void Image::single_point(tuple<int,int,double> points){
    /*
        Requires input of a tuple where:

        0 -- x coordinate of point
        1 -- y coordinate of point
        2 -- potential of point

        initialise vector as = {
            make_tuple(x_coord1, y_coord1, potential),
            make_tuple(x_coord2, y_coord2, potential),
            make_tuple(x_coord3, y_coord3, potential),
        }


    */


 
        int x_coord = get<0>(points);
        int y_coord = get<1>(points);
        double potential = get<2>(points);

        mesh[x_coord][y_coord] = potential;

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

<<<<<<< HEAD

  void Image::Rectangle(int corner_x, int corner_y, int length_x, int length_y,
			float V){
    /*
      Draw a boundary rectangle with fixed values inside and on the edges,
      its edges parallel to the grid-lines
      
      corner_x - x coordinate of top left corner
      corner_y - y coordinate of top left corner
      length_x - length in x coordinate
      length_y - length in y coordinate
     */
    

    // making sure the rectangle fits into the grid
    if(corner_x<0){
      length_x+=corner_x;
      corner_x=0;
    }
    if(corner_x+length_x>cols){
      length_x+=(corner_x+length_x)-cols;
    }
    if(corner_y<0){
      length_y+=corner_y;
      corner_y=0;
    }
    if(corner_y+length_y>rows){
      length_y+=(corner_y+length_y)-rows;
    }

    for(int i=0;i<length_x;i++){
      for(int j=0;j<length_y;j++){
	mesh[corner_x+i][corner_y+j]=V;
	change_indices[corner_x+i][corner_y+j]=false;
      }
    }

  }
}
=======
}



void Image::circle_alt(int centre_x, int centre_y, float radius, map<string,double> params, map<string,bool> fix_dict){
  
int rows = mesh.size(), cols = mesh[0].size();

  
  for(int i = 0; i != rows; i++){
    for(int j = 0; j != cols; j++){
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
>>>>>>> 246125bbbd41fa4605c022d1122f935870f38243
