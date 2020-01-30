#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
  
int main(){ 
    
    ofstream myfile;
    myfile.open ("grid.csv");
    
    int b1 = 20; // 1st potential boundary
    int b2 = -20; // 2nd potential boundary
    int n = 100; // width of vector matrix
    int m = 100; // height of vector matrix
    int h = 5; // 1/2 height of boundaries inside the field
    int w = 5; // 1/2 width of boundaries
  
    vector<vector<int> >  vec( n , vector<int> (m,1));
    vector<vector<bool> > check( n, vector<bool> (m, true));
  
    int gap = (n/4)-w; // this is the gap between each boundary within field
    int mid = n/2; // this is the midpoint between upper and lower boundaries
    
    for (int i=0; i<m;i++){
        vec[0][i]=0;
        vec[n-1][i]=0;
        check[0][i]=false;
        check[n-1][i]=false;
    }
    
    for(int i = mid-h; i < mid+h; i++){
        for(int j = gap; j < gap+2*w; j++){
            vec[i][j]=0;
            check[i][j]=false;
        }
        for(int j = 2*gap; j < 2*gap+2*w; j++){
            vec[i][j]=b1;
            check[i][j]=false;
        }
        for(int j = 3*gap; j < 3*gap+2*w; j++){
            vec[i][j]=b2;
            check[i][j]=false;
        }
        for(int j = 4*gap; j < 4*gap+2*w; j++){
            vec[i][j]=0;
            check[i][j]=false;
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            myfile << vec[i][j] << ";";
        }
        myfile << "\n"; 
    }   
    
    myfile.close();
    
    ofstream myfile2;
    myfile2.open("check.csv");
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            myfile2 << check[i][j] << ";";
        }
        myfile2 << "\n"; 
    }   
  
    myfile2.close();
  
return 0; 
} 