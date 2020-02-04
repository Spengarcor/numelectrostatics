#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <tuple>
#include "eBoundarySolver.h"

using namespace std;


int main(){

    int rows = 300, cols = 300;

    //use Image object to draw shapes (initialise)
    eBoundarySolver Q3(rows,cols);


    Q3.rectangle(0,0,5,cols,0);
    Q3.rectangle(rows-6,0,5,cols,0);


    Q3.rectangle(150,30,45,60,0);
    Q3.rectangle(150,100,45,60,10);
    Q3.rectangle(150,170,45,60,-10);
    Q3.rectangle(150,240,45,60,0);


    Q3.relaxPotential(0.5, 0.0001, 10000);

    Q3.save_to_csv("Q3");

    return 0;

}