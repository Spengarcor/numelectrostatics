#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include "eBoundarySolver.h"
#include "cpucon.h"

using namespace std;

int main(){
    
    //Accuracy lower threshold	
    double a = 1;

    for (int i=0; i<6; i++) {
    	a/=10;	
	
    	//creating vector of user defined type CPUData	
    	std::vector<CPUdata> snapshot1;
    	std::vector<CPUdata> snapshot2;	
    
   	 //Reading CPU State time snapshot 1
   	 Read Snapshot1;
   	 Snapshot1.ReadCPUdata(snapshot1);
		
   	 int rows = 500, cols = 500;

   	 eBoundarySolver Q1(rows, cols);

   	 //Set parameters for circle method
   	 map<string,double> outer_circle_params ={
   	     {"INSIDE", 0},
   	     {"BOUNDARY", 1.5},
   	     {"OUTSIDE", 1.5}
   	 };

   	 map<string,bool> outer_circle_fix_dict = {
   	     {"INSIDE", false},
   	     {"BOUNDARY", true},
   	     {"OUTSIDE", true}
   	 };

   	 Q1.circle(250,250,200, outer_circle_params, outer_circle_fix_dict);


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

   	 Q1.circle(250,250,100, inner_circle_params, inner_circle_fix_dict);


    	Q1.relaxPotential_J(a,100000);// put desired accuracy and max iterations 

    	Q1.save_to_csv("Q1");
	
    	//Reading CPU State time snapshot 2
    	Read Snapshot2;
    	Snapshot2.ReadCPUdata(snapshot2);

    	//Calulcating CPU consumption and CPU time, and saving to CPUAnalysisX.csv	
    	Save CPUAnalysis;
   	CPUAnalysis.SaveCPUdata(snapshot1, snapshot2, a);	      		
    }
    return 0;
}
