#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <tuple>
#include <chrono>
#include <thread>
#include <sstream>
#include <chrono>
#include <thread>
#include <sstream>
#include "eBoundarySolver.h"
#include "cpucon.h"

using namespace std;

int main(){

    //no. of Num Solver iterations      
    int n = 10;
	
    for (int i=0; i<4; i++) {	
    	n*=10;

    	//creating vector of user defined type CPUData      
    	std::vector<CPUdata> snapshot1;
    	std::vector<CPUdata> snapshot2;
    
   	 //Reading CPU State time snapshot 1
   	 Read Snapshot1;
   	 Snapshot1.ReadCPUdata(snapshot1);	

   	 int rows = 1000, cols = 1000;

    	//use Image object to draw shapes (initialise)
    	eBoundarySolver Q3(rows,cols);


    	Q3.rectangle(0,0,5,cols,0);
    	Q3.rectangle(rows-6,0,5,cols,0);


    	Q3.rectangle(110,450,150,100,0);
    
    	Q3.rectangle(330,450,150,100,10); //500 = (var1+50)+40
    	Q3.rectangle(520,450,150,100,-10);
    	Q3.rectangle(710,450,150,100,0);


    	Q3.relaxPotential_J(n);

    	Q3.save_to_csv("Q3_SOR");

    	//Reading CPU State time snapshot 2
    	Read Snapshot2;
    	Snapshot2.ReadCPUdata(snapshot2);
        
    	//Calulcating CPU consumption and CPU time, and saving to CPUAnalysisX.csv  
    	Save CPUAnalysis;
    	CPUAnalysis.SaveCPUdata(snapshot1, snapshot2, n);
    }	
    return 0;
}
