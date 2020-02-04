#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <map>
#include <string>
#include <tuple>
#include <fstream>
#include "eBoundarySolver.h"

using namespace std;



//////////////////////////////////////////
//             Constructors             //
//////////////////////////////////////////

eBoundarySolver::eBoundarySolver(int rows_in, int cols_in){

    rows = rows_in; cols = cols_in;

    vector<vector<double>> blank_mesh(rows, vector<double>(cols, 0));
    vector<vector<bool>> blank_fixed_indices(rows, vector<bool>(cols, false));

    mesh = blank_mesh;
    fixed_indices = blank_fixed_indices;

}


//////////////////////////////////////////
//       Boundary Drawing Methods       //
//////////////////////////////////////////

void eBoundarySolver::single_point(tuple<int,int,double> point, bool fixed){
    /*
        Requires input of a tuple where:

        0 -- x coordinate of point
        1 -- y coordinate of point
        2 -- potential of point

        Side Effect -- sets the given point to 
                        the given potential 
    */


        int x_coord = get<0>(point);
        int y_coord = get<1>(point);
        double potential = get<2>(point);

        mesh[x_coord][y_coord] = potential;
        fixed_indices[x_coord][y_coord] = fixed;

}




void eBoundarySolver::rectangle(int corner_x, int corner_y, int length_x, int length_y,
			float V){
  /*
    Draw a boundary rectangle with fixed values inside and on the edges,
    its edges parallel to the grid-lines
    
    corner_x - x coordinate of top left corner
    corner_y - y coordinate of top left corner
    length_x - length in x coordinate
    length_y - length in y coordinate
   */
  

  //Change to throw error rather than change position of rectangle

  // making sure the rectangle fits into the grid
  if(corner_x < 0){
    length_x += corner_x;
    corner_x = 0;
  }
  if(corner_x + length_x > cols){
    length_x += (corner_x + length_x) - cols; 
  }
  if(corner_y < 0){
    length_y += corner_y;
    corner_y = 0;
  }
  if(corner_y + length_y > rows){
    length_y += (corner_y + length_y) - rows; 
  }

  for(int i=0;i<length_x;i++){
    for(int j=0;j<length_y;j++){
	      mesh[corner_x+i][corner_y+j]=V;
	      fixed_indices[corner_x+i][corner_y+j]=true;
    }
  }

}


void eBoundarySolver::circle(int centre_x, int centre_y, float radius, map<string,double> params, map<string,bool> fix_dict){

  for(int i = 0; i != rows-1; i++){
    for(int j = 0; j != cols-1; j++){
      float dist{(i-centre_x)*(i-centre_x) + (j-centre_y)*(j-centre_y)};

        // checking if a point is in the circle from the equation of a circle
        if(radius*radius<dist){
            if(fix_dict["OUTSIDE"]){
    	        mesh[i][j] = params["OUTSIDE"]; 
                fixed_indices[i][j] = true; 
            }
        }
        else{
            if(fix_dict["INSIDE"]){
                mesh[i][j] = params["INSIDE"];
                fixed_indices[i][j] = true;
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
            fixed_indices[i][j] = true;
	        }
        }
    }
 }
}


//////////////////////////////////////////
//          Relaxation Methods          //
//////////////////////////////////////////

double eBoundarySolver::relaxPotential(double del, int max_iter){

     /*
        p - relaxation parameter
        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on the number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = (double) INT_MAX; //CHANGE BACK TO 2*del
    int iter_count =0;

    //Values needed for equations
    double hx = 1 / (double)rows, hy = 1 / (double)cols;
    double alpha = pow(hx/hy, 2);



    while(change > del && iter_count < max_iter){

        //Initialise change as will keep a running total for each mesh point
        change = 0;

        //Loop over all points
        for(int i = 0; i != rows; ++i){ 
            for(int j = 0; j != cols; ++j){
            
                
                if(fixed_indices[i][j]){

                    continue;

                } else {

                    //save original value for change calculation
                    double original_potential = mesh[i][j];                


                    //Basic handling of non-boundary edges
                    //For edges, just take the current value so the average is slightly weighted towards its current value
                    double x_before = i == 0 ? mesh[i][j] : mesh[i-1][j];
                    double x_after = i == rows - 1 ? mesh[i][j] : mesh[i+1][j];
                    double y_before = j == 0 ? mesh[i][j] : mesh[i][j-1];
                    double y_after = j == cols - 1 ? mesh[i][j] : mesh[i][j+1]; 

                    mesh[i][j] = 1/(2 *(1 + alpha) ) 
                             * ( x_before + x_after + alpha*(y_before + y_after) );

                    

                    double difference = mesh[i][j] - original_potential;
                    change += difference * difference; // add difference squared

                }
            }
        }


        //get RMS of change
        change = sqrt( change / (rows*cols) );
        //keep track of number of iterations
        ++iter_count;
    }

    return change;

}


//////////////////////////////////////////
//             File Methods             //
//////////////////////////////////////////

void eBoundarySolver::save_to_csv(string fname){

    ofstream csv_file;

    csv_file.open(fname + ".csv");

    for(int i = 0; i != rows; ++i){
        for(int j = 0; j != cols; ++j){
    
            csv_file << mesh[i][j];

            if(j != mesh.size()-1){
                csv_file << ";";
            }

        }
        csv_file << "\n";
    }

    csv_file.close();

}

