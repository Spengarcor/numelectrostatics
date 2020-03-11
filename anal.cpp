#include <vector>
#include <cmath>

vector<vector<double>> analQ1(int rows,int cols,double V,double r1,double r2,
			      int c_x,int c_y){
  vector<vector<double>> solution(rows,vector<double>(cols,0));
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      double dist = sqrt((c_x-i)*(c_x-i)+(c_y-j)*(c_y-j));
      if(dist<r1){
	solution[i][j] = 0;
      }
      else{
	if(dist>r2){
	  solution[i][j] = V;
	}
	else{
	  solution[i][j] = V*(log(dist/r1)/log(r2/r1));
	}
      }
    }
  }
  return solution;
}

vector<vector<double>> analQ2(int rows,int cols,double V,
			      double r,int c_x,int c_y,
			      int x_min,int x_max){
  vector<vector<double>> solution(rows,vector<double>(cols,0));
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      double dist = sqrt((c_x-i)*(c_x-i)+(c_y-j)*(c_y-j));
      if(i<=x_min){
	solution[i][j] = V;
      }
      else{
	if(i>=x_max){
	  solution[i][j] = -V;
	}
	else{
	  if(dist<=r){
	    solution[i][j] = 0;
	  }
	  else{
	    double cosine = (i - c_x)/dist;
	    solution[i][j] = -(2*V/(x_max-x_min))*(dist-(r*r)/dist)*cosine;
	  }
	}
      }
    }
  }
  return solution;
}

double mean_stdev(int rows, int cols,
		  vector<vector<double> A, vector<vector<double> B){
  double stdev = 0;
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      stdev += (A[i][j]-B[i][j])*(A[i][j]-B[i][j]);
    }
  }
  return sqrt(stdev/(cols*rows));
}

double mean_abs(int rows, int cols,
		vector<vector<double> A, vector<vector<double> B){
  double stdev = 0;
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      stdev += std::abs(A[i][j]-B[i][j]);
    }
  }
  return stdev/(cols*rows);
}
