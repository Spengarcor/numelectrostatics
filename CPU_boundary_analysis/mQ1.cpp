#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
//#include <fstream>
#include "modified_eBS.h"
#include "cpucon.h"

using namespace std;


int main(){
  int n = 100;
  
  for (int i=0; i<4; i++) {
    n*=10;
    
    //creating vector of user defined type CPUData	
    std::vector<CPUdata> snapshot1;
    std::vector<CPUdata> snapshot2;	
    
    //Reading CPU State time snapshot 1
    Read Snapshot1;
    Snapshot1.ReadCPUdata(snapshot1);
    int rows = 200, cols = 200;
    /*
    eBoundarySolver Q1_J(rows, cols);
    Q1_J.circle(50,50,45,nan(""),1.5,1.5);
    Q1_J.circle(50,50,25,0,0,nan(""));
    Q1_J.relaxPotential_J(n);
    //Q1_J.save_to_csv("Q1_J");
    
    eBoundarySolver Q1_GS(rows, cols);
    Q1_GS.circle(50,50,45,nan(""),1.5,1.5);
    Q1_GS.circle(50,50,25,0,0,nan(""));
    Q1_GS.relaxPotential_GS(n);
    //Q1_GS.save_to_csv("Q1_GS");
    */
    eBoundarySolver Q1_SOR(rows, cols);
    Q1_SOR.circle(100,100,90,nan(""),1.5,1.5);
    Q1_SOR.circle(100,100,50,0,0,nan(""));
    Q1_SOR.relaxPotential_SOR(n);
    //Q1_SOR.save_to_csv("Q1_SOR");
    
    Q1_SOR.save_to_csv("Q1"+to_string(i));
    
    //Reading CPU State time snapshot 2
    Read Snapshot2;
    Snapshot2.ReadCPUdata(snapshot2);
    
    //Calulcating CPU consumption and CPU time, and saving to CPUAnalysisX.csv	
    Save CPUAnalysis;
    CPUAnalysis.SaveCPUdata(snapshot1, snapshot2, n);	      			
  }
  return 0;
}
