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

  for(int i = 0; i != rows; i++){
    for(int j = 0; j != cols; j++){
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

double eBoundarySolver::relaxPotential_J(double del, int max_iter, bool interpolating){

     /*
        An implementation of the Jacobi method for relaxaing an ODE

        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on the number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = (double) INT_MAX; 
    int iter_count = 0;

    //Values needed for equations
    double hx = 1 / (double)rows, hy = 1 / (double)cols;
    double alpha = pow(hx/hy, 2);


    std::vector<std::vector<double>> original_potential = mesh;
    
    
    std::vector<std::vector<double>> analytical_sol = analQ2(rows, cols, 20, 60, 250, 250, 1, cols-1);

    while(change > del && iter_count < max_iter){

        //Initialise change as will keep a running total for each mesh point
        change = 0;

        vector<vector<double>> original_potential = mesh;





        //Loop over all points
        for(int i = 0; i != rows; ++i){ 
            for(int j = 0; j != cols; ++j){
            
                
                if(fixed_indices[i][j]){

                    continue;

                } else {



                    
                    double x_before = 0;
                    double x_after = 0;
                    double y_before = 0;
                    double y_after = 0;

                    if(interpolating){
                        x_before = i == 0 ? lagInterpolate(0, i-1, j, 3) : original_potential[i-1][j];
                        x_after = i == rows - 1 ? lagInterpolate(0, i-1, j, 3) : original_potential[i+1][j];
                        y_before = j == 0 ? lagInterpolate(1, i, j-1, 3) : original_potential[i][j-1];
                        y_after = j == cols - 1 ? lagInterpolate(1, i, j-1, 3) : original_potential[i][j+1];  
                    
                    } else {
                        //Basic handling of non-boundary edges
                        //For edges, just take the current value so the average is slightly weighted towards its current value
                        x_before = i == 0 ? original_potential[i][j] : original_potential[i-1][j];
                        x_after = i == rows - 1 ? original_potential[i][j] : original_potential[i+1][j];
                        y_before = j == 0 ? original_potential[i][j] : original_potential[i][j-1];
                        y_after = j == cols - 1 ? original_potential[i][j] : original_potential[i][j+1]; 


                    }

                    mesh[i][j] = 1/(2 *(1 + alpha) ) 
                             * ( x_before + x_after + alpha*(y_before + y_after) );

                    

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


double eBoundarySolver::relaxPotential_GS(double del, int max_iter, bool interpolating){

     /*
        An implementation of the Gauss-Seidel method for relaxaing an ODE
        
        del - the required accuracy before stopping relaxation
        max_iter - a ceiling on the number of iterations that can occur to give reasonable runtime 
    */



    //Need to know how big a change each step of relaxation causes 
    //so we can determine when to stop i.e. when diminished returns
    double change = (double) INT_MAX; 
    int iter_count = 0;

    //Values needed for equations
    double hx = 1 / (double)rows, hy = 1 / (double)cols;
    double alpha = pow(hx/hy, 2);


    std::vector<std::vector<double>> analytical_sol = analQ2(rows, cols, 20, 60, 250, 250, 1, cols-1);


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

                    
                    double x_before = 0;
                    double x_after = 0;
                    double y_before = 0;
                    double y_after = 0;

                    if(interpolating){
                        x_before = i == 0 ? lagInterpolate(0, i-1, j, 3) : mesh[i-1][j];
                        x_after = i == rows - 1 ? lagInterpolate(0, i-1, j, 3) : mesh[i+1][j];
                        y_before = j == 0 ? lagInterpolate(1, i, j-1, 3) : mesh[i][j-1];
                        y_after = j == cols - 1 ? lagInterpolate(1, i, j-1, 3) : mesh[i][j+1]; 
                    
                    } else {
                        //Basic handling of non-boundary edges
                        //For edges, just take the current value so the average is slightly weighted towards its current value

                        x_before = i == 0 ? mesh[i][j] : mesh[i-1][j];
                        x_after = i == rows - 1 ? mesh[i][j] : mesh[i+1][j];
                        y_before = j == 0 ? mesh[i][j] : mesh[i][j-1];
                        y_after = j == cols - 1 ? mesh[i][j] : mesh[i][j+1]; 

                    }


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

double eBoundarySolver::relaxPotential_SOR(double del, int max_iter, bool interpolating){

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
    double hx = 1 / (double)50, hy = 1 / (double)50;
    double hxq= 1 / (double)rows;
    double alpha = pow(hx/hy, 2);

    double omega = 2/ ( 1 + sin(M_PI*hxq) );
    double one_minus_omega = 1 - omega; 


    
    std::vector<std::vector<double>> analytical_sol = analQ2(rows, cols, 20, 60, 250, 250, 1, cols-1);



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

                    double x_before = 0;
                    double x_after = 0;
                    double y_before = 0;
                    double y_after = 0;

                    if(interpolating){
                        x_before = i == 0 ? lagInterpolate(0, i-1, j, 3) : mesh[i-1][j];
                        x_after = i == rows - 1 ? lagInterpolate(0, i-1, j, 3) : mesh[i+1][j];
                        y_before = j == 0 ? lagInterpolate(1, i, j-1, 3) : mesh[i][j-1];
                        y_after = j == cols - 1 ? lagInterpolate(1, i, j-1, 3) : mesh[i][j+1]; 
                    
                    } else {
                        //Basic handling of non-boundary edges
                        //For edges, just take the current value so the average is slightly weighted towards its current value

                        x_before = i == 0 ? mesh[i][j] : mesh[i-1][j];
                        x_after = i == rows - 1 ? mesh[i][j] : mesh[i+1][j];
                        y_before = j == 0 ? mesh[i][j] : mesh[i][j-1];
                        y_after = j == cols - 1 ? mesh[i][j] : mesh[i][j+1]; 

                    }


                    double average_potential = 1/(2 *(1 + alpha) ) 
                             * ( x_before + x_after + alpha*(y_before + y_after) );

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
//             Interpolation            //
//////////////////////////////////////////


//Use three points
double eBoundarySolver::lagInterpolate(int axis, int x_coord, int y_coord, int num_points){

    double zp = 0;

    int coord = (axis == 0 ? x_coord : y_coord); 

    //Need to ensure interpolation is in the correct direction
    //Can be left or right and the sign of change determines this
    int change = coord < 0 ? -1 : 1;

    for(int i = coord - (change * num_points) ; i !=coord; i += change ){

        double p = 0;

        for( int j = coord - (change * num_points); j != coord; j += change){

            if( i != j ) p *= (coord - j) / (i - j);
            
        }

        int mesh_x = (axis == 0 ? i : x_coord);
        int mesh_y = (axis == 1 ? i : y_coord);

        zp += p * mesh[mesh_x][mesh_y];
    }

    return zp;

}





vector<vector<double>> eBoundarySolver::analQ1(int rows,int cols,double V,double r1,double r2, int c_x,int c_y){

  vector<vector<double>> solution(rows,vector<double>(cols,0));
  
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
        
        double dist = sqrt((c_x-i)*(c_x-i)+(c_y-j)*(c_y-j));
        if(dist<r1){
	        solution[i][j] = 0;
        } else {

    	    if(dist>r2){
	            solution[i][j] = V;
	        } else {
                solution[i][j] = V*(log(dist/r1)/log(r2/r1));
	        }
        }
    }
  }

  return solution;
}



vector<vector<double>> eBoundarySolver::analQ2(int rows,int cols,double V, double r,int c_x,int c_y, int x_min,int x_max){

  vector<vector<double>> solution(rows,vector<double>(cols,0));
  
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
  
        double dist = sqrt((c_x-i)*(c_x-i)+(c_y-j)*(c_y-j));
    
        if(i<=x_min){
        	solution[j][i] = V;
        } else {

	        if(i>=x_max){
	          solution[j][i] = -V;
	        } else {

	          if(dist<=r){

	            solution[j][i] = 0;

	          } else {

	            double cosine = (i - c_x)/dist;
	            solution[j][i] = -(2*V/(x_max-x_min))*(dist-(r*r)/dist)*cosine;

	          }
	        }
      }
    }
  }
  return solution;
}







double eBoundarySolver::get_abs_error(int rows, int cols, vector<vector<double>> A, vector<vector<double>> B){

    double err = 0;

    int ratio = rows / 50; 


  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      
      
      err += std::abs(A[i][j]-B[i][j]);
      

    }
  }

  return err;

}





//////////////////////////////////////////
//             File Methods             //
//////////////////////////////////////////

void eBoundarySolver::save_to_csv(string fname){

    ofstream csv_file;

    int ratio = rows / 50; 

    csv_file.open(fname + "ignore.csv");

    for(int i = 0; i != rows; ++i){
        for(int j = 0; j != cols; ++j){
    
            if(i%ratio == 0 && j%ratio == 0){
              csv_file << mesh[i][j];

              if(j != mesh.size()-1){
                  csv_file << ";";
              }
            }

        }
        csv_file << "\n";
    }

    csv_file.close();

}	

/*
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
*/

void eBoundarySolver::save_errors(int iters, double abs_error, double change){

    ofstream csv_file;

    string fname = "CSV_files//errors/Q2_err_J"; 

    csv_file.open(fname + ".csv", std::ios_base::app);

    csv_file << iters << ";";
    csv_file << abs_error << ";";
    csv_file << change << "\n";


}
