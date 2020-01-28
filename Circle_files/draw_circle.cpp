#include <iostream>
#include <cmath>

int main(int argc, char ** argv){
  if(argc!=4){
    std::cout << "Pass horizontal size, vertical size and radius\n";
    return 1;
  }
  int hor{atoi(argv[1])};
  int vert{atoi(argv[2])};
  float radius{atof(argv[3])};
  
  float centre[2] = {float(hor)/2,float(vert)/2};
  
  char grid[hor][vert];
  for(int i=0;i<hor;i++){
    for(int j=0;j<vert;j++){
      float dist{(i-centre[0])*(i-centre[0]) + (j-centre[1])*(j-centre[1])};
      
      if(radius*radius>dist){
	grid[i][j] = 'I';
      }
      else{
	grid[i][j] = ' ';
      }

      
      if(fabs(sqrt(dist)-radius)<sqrt(2)){
	if(fabs(sqrt(fabs(radius*radius-pow(centre[0]-float(i),2)))-
		fabs(float(j)-centre[1]))
	   <=0.5 || 
	   fabs(sqrt(fabs(radius*radius-pow(centre[1]-float(j),2)))-
		fabs(float(i)-centre[0]))
	   <=0.5){
	  grid[i][j] = 'B';
	}
      }
      std::cout << grid[i][j];
    }
    std::cout << "\n";
  }
  return 0;
}
