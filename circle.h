#include <iostream>
#include <cmath>

void Grid::circle(int centre_x, int centre_y, float radius, SETTINGS){
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
	grid[i][j] = SETTINGS[INSIDE];
      }
      else{
	grid[i][j] = SETTINGS[OUTSIDE];
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
	  grid[i][j] = SETTINGS[BOUNDARY];
	}
      }
    }
  }
}
  
