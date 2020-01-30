#include <iostream>
#include <vector>

using namespace std;
  
int main(){ 
    int b1 = 20; // 1st potential boundary
    int b2 = -20; // 2nd potential boundary
    int n = 60; // width of vector matrix
    int m = 60; // height of vector matrix
    int h = 2; // 1/2 height of boundaries inside the field
    int w = 2; // 1/2 width of boundaries
  
    vector<vector<int> >  vec( n , vector<int> (m,1));
  
    int gap = 0.25*(n-(8*w)); // this is the gap between each boundary within field
    int mid = n/2; // this is the midpoint between upper and lower boundaries
    
    for (int i=0; i<m;i++){
        vec[0][i]=0;
        vec[n-1][i]=0;
    }
    
    for(int i = mid-h; i < mid+h; i++){
        for(int j = gap; j < gap+2*w; j++){
            vec[i][j]=0;
        }
        for(int j = 2*gap; j < 2*gap+2*w; j++){
            vec[i][j]=b1;
        }
        for(int j = 3*gap; j < 3*gap+2*w; j++){
            vec[i][j]=b2;
        }
        for(int j = 4*gap; j < 4*gap+2*w; j++){
            vec[i][j]=0;
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << vec[i][j] << " ";
        }
        cout << "\n"; 
    }   
  
return 0; 
} 
