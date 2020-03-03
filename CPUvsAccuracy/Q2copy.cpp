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
#include "eBoundarySolver.h"
#include "cpucon.h"

using namespace std;

int main(){

    //Accuracy lower threshold  
    double a = 1;
 
    for (int i=0; i<3; i++) {
    	a/=10;
        
    	//creating vector of user defined type CPUData      
    	std::vector<CPUdata> snapshot1;
    	std::vector<CPUdata> snapshot2;
   
   	 //Reading CPU State time snapshot 1
   	 Read Snapshot1;
   	 Snapshot1.ReadCPUdata(snapshot1);	

   	 int rows = 500, cols = 500;

   	 eBoundarySolver Q2(rows,cols);

   	 Q2.rectangle(0,0,rows,1,20);
   	 Q2.rectangle(0,cols-1,rows,1,-20);

   	 map<string,double> inner_circle_params ={
   	     {"INSIDE", 0},
   	     {"BOUNDARY", 0},
   	     {"OUTSIDE", 0}
   	 };

   	 map<string,bool> inner_circle_fix_dict = {
   	     {"INSIDE", true},
   	     {"BOUNDARY", true},
   	     {"OUTSIDE", false}
   	 };
	
	 Q2.circle(250,250,60, inner_circle_params, inner_circle_fix_dict);

	 Q2.relaxPotential_J(a, 100000);

	 Q2.save_to_csv("Q2_SOR");

	 //Reading CPU State time snapshot 2
   	 Read Snapshot2;
	 Snapshot2.ReadCPUdata(snapshot2);
    
    	//Calulcating CPU consumption and CPU time, and saving to CPUAnalysisX.csv  
    	Save CPUAnalysis;
    	CPUAnalysis.SaveCPUdata(snapshot1, snapshot2, a);
    }
    return 0;
}
