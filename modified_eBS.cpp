#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <map>
#include <string>
#include <tuple>
#include <fstream>
#include <climits>
#include "modified_eBS.h"

using namespace std;

//////////////////////////////////////////
//             Constructors             //
//////////////////////////////////////////

eBoundarySolver::eBoundarySolver(int rows_in, int cols_in){

    rows = rows_in; cols = cols_in;

    vector<vector<double>> blank_mesh(rows, vector<double>(cols, 0));
    vector<vector<int>> blank_fixed_indices(rows, vector<int>(cols, 0));
    vector<vector<vector<double>>> blank_boundaries(rows,
						    vector<vector<double>>( 
						    cols,
						    vector<double>(8,nan(""))));

    mesh = blank_mesh;
    fixed_indices = blank_fixed_indices;
    boundaries = blank_boundaries;

}


//////////////////////////////////////////
//       Boundary Drawing Methods       //
//////////////////////////////////////////

void eBoundarySolver::single_point(tuple<int,int,double> point, bool fixed ){
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
	if(fixed){
	  fixed_indices[x_coord][y_coord] = 1;
	}
	else{
	  fixed_indices[x_coord][y_coord] = 0;
	}

}




void eBoundarySolver::rectangle(int corner_x, int corner_y, int length_x,
				int length_y, double V){
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
	      fixed_indices[corner_x+i][corner_y+j]=1;
    }
  }

}


void eBoundarySolver::circle(int centre_x, int centre_y, double radius,
			     double inside_V, double boundary_V,
			     double outside_V){
  
  for(int i = 0; i != rows-1; i++){
    for(int j = 0; j != cols-1; j++){
      float dist{(i-centre_x)*(i-centre_x) + (j-centre_y)*(j-centre_y)};
      
      // checking if a point is in or out the circle from the equation
      // of a circle
      if(radius*radius<dist){
	if(!isnan(outside_V)){
	  mesh[i][j] = outside_V; 
	  fixed_indices[i][j] = 1; 
	}
      }
      if(radius*radius>=dist){
	if(!isnan(inside_V)){
	  mesh[i][j] = inside_V;
	  fixed_indices[i][j] = 1;
	}
      }
      // a third condition for points exactly on the boundary could be added
      // if the difference is smaller than some accuracy limit

      // So to avoid checking every point for a boundary
      if(fabs(sqrt(dist)-radius)<sqrt(2)){
	
	// if the circle crosses a grid line within 0.5 from the point
	double d_y = fabs(j-centre_y)
	             - sqrt(fabs(radius*radius-(centre_x-i)*(centre_x-i)));
	double d_x = fabs(i-centre_x)
	             - sqrt(fabs(radius*radius-(centre_y-j)*(centre_y-j)));

	if(fabs(d_x)<1){
	  if(i>centre_x){
	    if(d_x<0){ //positive x
	      change_boundary(i, j, 0, fabs(d_x), boundary_V);
	    }
	    if(d_x>0){ //negative x
	      change_boundary(i, j, 2, fabs(d_x), boundary_V);
	    }
	  }
	  if(i<centre_x){
	    if(d_x<0){ //negative x
	      change_boundary(i, j, 2, fabs(d_x), boundary_V);
	    }
	    if(d_x>0){ //poasitive x
	      change_boundary(i, j, 0, fabs(d_x), boundary_V);
	    }
	  }
	}
	if(fabs(d_y)<1){
	  if(j>centre_y){
	    if(d_y<0){ //positive y
	      change_boundary(i, j, 1, fabs(d_y), boundary_V);
	    }
	    if(d_y>0){ //negative y
	      change_boundary(i, j, 3, fabs(d_y), boundary_V);
	    }
	  }
	  if(j<centre_y){
	    if(d_y<0){ //negative y
	      change_boundary(i, j, 3, fabs(d_y), boundary_V);
	    }
	    if(d_y>0){ //positive y
	      change_boundary(i, j, 1, fabs(d_y), boundary_V);
	    }
	  }
	}
      }
    }
  }
}


void eBoundarySolver::change_boundary(int i, int j, int dir,
				      double dis, double V){
  /*
    i, j - indices as in grid
    dir - direction: 0 - x positive
                     1 - y positive
                     2 - x negative
                     3 - y negative
    dis - new h for differentiation
    V - boundary potential
   */
  fixed_indices[i][j] = 2;
  if(isnan(boundaries[i][j][dir*2] || boundaries[i][j][dir*2]>dis)){
    boundaries[i][j][dir*2] = dis;
    boundaries[i][j][dir*2+1] = V;
  }
}


//////////////////////////////////////////
//          Relaxation Methods          //
//////////////////////////////////////////

double eBoundarySolver::relaxPotential_J(double del, int max_iter){

     /*
        An implementation of the Jacobi method for relaxaing an ODE

        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on the number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = (double) INT_MAX; 
    int iter_count =0;

    //Values needed for equations
    double hx = 1 / (double)rows, hy = 1 / (double)cols;
    double alpha = pow(hx/hy, 2);


    vector<vector<double>> original_potential = mesh;

    while(change > del && iter_count < max_iter){

        //Initialise change as will keep a running total for each mesh point
        change = 0;

        vector<vector<double>> original_potential = mesh;

        //Loop over all points
        for(int i = 0; i != rows; ++i){ 
            for(int j = 0; j != cols; ++j){
            
                
                if(fixed_indices[i][j]==1){

                    continue;

                }
		else {


                    //Basic handling of non-boundary edges
                    //For edges, just take the current value so the average is slightly weighted towards its current value
                    double x_before = i == 0 ? original_potential[i][j] : original_potential[i-1][j];
                    double x_after = i == rows - 1 ? original_potential[i][j] : original_potential[i+1][j];
                    double y_before = j == 0 ? original_potential[i][j] : original_potential[i][j-1];
                    double y_after = j == cols - 1 ? original_potential[i][j] : original_potential[i][j+1]; 
		    
		    if(fixed_indices[i][j]==0){
		      mesh[i][j] = 1/(2 *(1 + alpha) ) 
			* ( x_before + x_after + alpha*(y_before + y_after) );
		    }

		    if(fixed_indices[i][j]==2){
		      double hx_after, hx_before, hy_after, hy_before;
		      if(!isnan(boundaries[i][j][4])){
			hx_before = boundaries[i][j][4] * hx;
			x_before = boundaries[i][j][5];
		      }
		      else{
			hx_before = hx;
		      }
		      if(!isnan(boundaries[i][j][0])){
			hx_after = boundaries[i][j][0] * hx;
			x_after = boundaries[i][j][1];
		      }
		      else{
			hx_after = hx;
		      }
		      if(!isnan(boundaries[i][j][6])){
			hy_before = boundaries[i][j][6] * hy;
			y_before = boundaries[i][j][7];
		      }
		      else{
			hy_before = hy;
		      }
		      if(!isnan(boundaries[i][j][2])){
			hy_after = boundaries[i][j][2] * hy;
			y_after = boundaries[i][j][3];
		      }
		      else{
			hy_after = hy;
		      }

		      mesh[i][j] = ((x_before*hx_after + x_after*hx_before)/
				(hx_after + hx_before) * hy_after * hy_before +
			        (y_before*hy_after + y_after*hy_before)/	 			    (hy_after + hy_before) * hx_after * hx_before) /
			(hx_after * hx_before + hy_after * hy_before);
		    }
                    double difference = mesh[i][j] - original_potential[i][j];
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


double eBoundarySolver::relaxPotential_GS(double del, int max_iter){

     /*
        An implementation of the Gauss-Seidel method for relaxaing an ODE
        
        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on the number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = (double) INT_MAX; 
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
            
                
                if(fixed_indices[i][j]==1){

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

		    if(fixed_indices[i][j]==0){
		      mesh[i][j] = 1/(2 *(1 + alpha) ) 
			* ( x_before + x_after + alpha*(y_before + y_after) );
		    }

		    if(fixed_indices[i][j]==2){
		      double hx_after, hx_before, hy_after, hy_before;
		      if(!isnan(boundaries[i][j][4])){
			hx_before = boundaries[i][j][4] * hx;
			x_before = boundaries[i][j][5];
		      }
		      else{
			hx_before = hx;
		      }
		      if(!isnan(boundaries[i][j][0])){
			hx_after = boundaries[i][j][0] * hx;
			x_after = boundaries[i][j][1];
		      }
		      else{
			hx_after = hx;
		      }
		      if(!isnan(boundaries[i][j][6])){
			hy_before = boundaries[i][j][6] * hy;
			y_before = boundaries[i][j][7];
		      }
		      else{
			hy_before = hy;
		      }
		      if(!isnan(boundaries[i][j][2])){
			hy_after = boundaries[i][j][2] * hy;
			y_after = boundaries[i][j][3];
		      }
		      else{
			hy_after = hy;
		      }

		      mesh[i][j] = ((x_before*hx_after + x_after*hx_before)/
				(hx_after + hx_before) * hy_after * hy_before +
			        (y_before*hy_after + y_after*hy_before)/	 			    (hy_after + hy_before) * hx_after * hx_before) /
			(hx_after * hx_before + hy_after * hy_before);
		    }


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

double eBoundarySolver::relaxPotential_SOR(double del, int max_iter){

     /*
        An implementation of the SOR method for relaxaing an ODE
        
        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on the number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = (double) INT_MAX;
    int iter_count =0;

    //Values needed for equations
    double hx = 1 / (double)rows, hy = 1 / (double)cols;
    double alpha = pow(hx/hy, 2);

    double omega = 2/ ( 1 + sin(M_PI*hx) );
    double one_minus_omega = 1 - omega; 



    while(change > del && iter_count < max_iter){

        //Initialise change as will keep a running total for each mesh point
        change = 0;

        //Loop over all points
        for(int i = 0; i != rows; ++i){ 
            for(int j = 0; j != cols; ++j){
            
                
                if(fixed_indices[i][j]==1){

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

                    double average_potential;


		    if(fixed_indices[i][j]==0){
		      average_potential = 1/(2 *(1 + alpha) ) 
			* ( x_before + x_after + alpha*(y_before + y_after) );
		    }

		    if(fixed_indices[i][j]==2){
		      double hx_after, hx_before, hy_after, hy_before;
		      if(!isnan(boundaries[i][j][4])){
			hx_before = boundaries[i][j][4] * hx;
			x_before = boundaries[i][j][5];
		      }
		      else{
			hx_before = hx;
		      }
		      if(!isnan(boundaries[i][j][0])){
			hx_after = boundaries[i][j][0] * hx;
			x_after = boundaries[i][j][1];
		      }
		      else{
			hx_after = hx;
		      }
		      if(!isnan(boundaries[i][j][6])){
			hy_before = boundaries[i][j][6] * hy;
			y_before = boundaries[i][j][7];
		      }
		      else{
			hy_before = hy;
		      }
		      if(!isnan(boundaries[i][j][2])){
			hy_after = boundaries[i][j][2] * hy;
			y_after = boundaries[i][j][3];
		      }
		      else{
			hy_after = hy;
		      }

		      average_potential = ((x_before*hx_after + x_after*hx_before)/
				(hx_after + hx_before) * hy_after * hy_before +
			        (y_before*hy_after + y_after*hy_before)/	 			    (hy_after + hy_before) * hx_after * hx_before) /
			(hx_after * hx_before + hy_after * hy_before);
		    }

                    mesh[i][j] = one_minus_omega * mesh[i][j] + omega * average_potential;
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
