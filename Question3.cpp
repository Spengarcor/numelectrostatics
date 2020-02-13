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

    int rows = 1000, cols = 1000;

    //use Image object to draw shapes (initialise)
    eBoundarySolver Q3(rows,cols);


    Q3.rectangle(0,0,5,cols,0);
    Q3.rectangle(rows-6,0,5,cols,0);


    Q3.rectangle(110,450,150,100,0);
    
    Q3.rectangle(330,450,150,100,10); //500 = (var1+50)+40
    Q3.rectangle(520,450,150,100,-10);
    Q3.rectangle(710,450,150,100,0);


    Q3.relaxPotential_SOR(1e-5, 10000);

    Q3.save_to_csv("Q3_SOR");

    return 0;

}