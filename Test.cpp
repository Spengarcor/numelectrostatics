// For symetry, odd number for matrix size is ideal, means even number of values either side of the ground

#include <iostream>
#include <vector>

using namespace std;
  
int main(){ 
    int high = 20; // upper potential boundary
    int low = -20; // lower potential boundary
    int n = 41; // vector size
    int r = 6; // radius
  
    vector<vector<int> >  vec( n , vector<int> (n,0));
  
    int mid = 0;
  
    if ( n % 2 == 0) // n is even, take point that is closest to middle, i.e n/2.
        mid = n/2;
    else // n is odd, so take midpoint to be exact middle since even number of values surround our point
        mid = (n-1)/2;
        
    vec[mid][mid] = 2;
    
    for(int i = mid - r; i <= mid + r; i++){
        for(int j = mid - r; j <= mid + r; j++){
            if ((i-mid)*(i-mid) + (j-mid)*(j-mid) <= r*r){
                vec[i][j] = 1;
            }
        }
    }
    
    for (int i=0; i<n;i++){
        vec[i][0]=high;
        vec[i][n-1]=low;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << vec[i][j] << " ";
        }
        cout << "\n"; 
    }   
  
return 0; 
} 