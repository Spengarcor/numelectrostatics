//cpucon.cpp 

//Determines CPU consumption and total CPU time for numerical solver. Iterally saves results to csv file for each number of iteration used in solver.

//Need to declare vectors of data type CPUdata to store CPU data fetched from /proc/stat, in main
///*      std::vector<CPUData> snapshot1;
//        std::vector<CPUData> snapshot2; */

#include <fstream>
#include <iostream> //iostream class defined in fstream std::cout 
#include <string> //std::string
#include <vector> //std::vector
#include <sstream> //header providing string stream classes such as std::istringstream
#include <thread> //???
#include <chrono> //deals with time ie. measure time spans, specific points in time, real clocks 
#include "cpucon.h"

//Defining function which reads CPU data from /proc/stat
//Objects kept in std::vector passed as parameter to function (since function passed pointer)
void Read::ReadCPUdata(std::vector<CPUdata> & entries) {
	
	std::ifstream fileStat("/proc/stat"); //Opening /proc/stat for reading		
	std::string line; //declaring string to store line
	size_t counter = 0; //counter to stop reading after 5th line
 
	//reading lines 0-5 of /proc/stat
	while (counter < 5 && std::getline(fileStat, line)) {
		
		std::istringstream iss(line);	
		//Creating extra element at end of vector entries (which points to parameter passed) with entry pointing to it
		entries.emplace_back(CPUdata());
		CPUdata & entry = entries.back();
		
		//storing 10 different state times from element 1-11 (so not to include CPU title)  
		for (int i = 0; i < 11; i++) {
			
			if (i==0) {
				std::string dummy;
				iss >> dummy; //to get rid of cpu string in first element of iss
			} else {
				iss >> entry.times[i]; //entry points to last element of entries vector
			}
		}
		
		counter++;
	}
}

//Defining function used in SaveCPUdata which calculates Idle time of CPU's based on CPU data fetched by ReadCPUdata. Takes in element of entries[i] of type CPUData and adds idle state times together.
size_t Save::TimeIdle(const CPUdata & s) {

	return s.times[3/*S_IDLE*/] + s.times[4/*S_IOWAIT*/];	
}

//Defining function used in SaveCPUdata which calculates active time of CPU's based on CPU data fetched by ReadCPUdata
size_t Save::TimeActive(const CPUdata & s) {	

	return s.times[0/*S_USER*/] + s.times[1/*S_NICE*/] + s.times[2/*S_SYSTEM*/] + s.times[5/*S_IRQ*/] + s.times[6/*S_SOFTIRQ*/] + s.times[7/*S_STEAL*/] + s.times[8/*S_GUEST*/] + s.times[9/*S_GUEST_NICE*/];

}

//Defining function which calculates the active CPU time as a % of total CPU time ((active time)/(active time + idle time))
//Saves this iteratively to separate cpuanalysis.csv files for each CPU core and CPU total, along with total CPU time and number of iterations used in num solver 'n'
void Save::SaveCPUdata(const std::vector<CPUdata> & snapshot1, const std::vector<CPUdata> & snapshot2, const size_t n) {
		
	//Declaring constant stating size of snapshot, so that for loop can run through each element
	const size_t Num_of_Entries = snapshot1.size();	
	
	//Saving CPU consumption and CPU time for each core to different CPUanalysis(0-4).csv files. Where 0 is CPU total, 1 is CPU core 1, etc.
		
	//Running through each line of /proc/stat to find CPU consumption and total CPU time
	for (size_t i=0; i < Num_of_Entries; i++) {	
		
		//Declaring constant of type CPUdata to store element of vector<CPUData> entries[i]
		const CPUdata & s1 = snapshot1[i];
		const CPUdata & s2 = snapshot2[i];
			
		//Calculating active time, idle time, and total time of numerical solver, casting RHS as floats to match LHSi
		auto ACTIVE_TIME = static_cast<int>(TimeActive(s2)) - static_cast<int>(TimeActive(s1)); //difference in active time between each snapshot
		auto IDLE_TIME = static_cast<int>(TimeIdle(s2)) - static_cast<int>(TimeIdle(s1)); //difference in idle time between each snapshot
		auto TOTAL_TIME = ACTIVE_TIME + IDLE_TIME;
		
		//Calculating CPU Consumption by dividing active CPU time between snapshots by total CPU time between snapshots
		const float CPUConsumption = 100*(static_cast<float>(ACTIVE_TIME)/static_cast<float>(TOTAL_TIME));
			
		//Using stringstream to create string that can be used to loop through different save files and pipe results
		std::stringstream ss;
		ss << "cpuanalysis" << i << ".csv";
		std::string filename = ss.str();
			
		//Opening file
		std::ofstream file;
		file.open(filename, std::ios_base::app); //.c_str() returns pointer to c-string representation of 'file' string object's value, and std::ios_base::app to append instead of overwrite
			
		//Writing results into file	
		file << n << ", " << CPUConsumption << ", " << TOTAL_TIME << ", " << ACTIVE_TIME << ", " << IDLE_TIME << std::endl;

		//Closing file
		file.close();
	}
}	 
