//cpucon.cpp 

//Determines CPU consumption and total CPU time for numerical solver. Iterally saves results to csv file for each number of iteration used in solver.

#include <fstream>
#include <iostream> //iostream class defined in fstream std::cout 
#include <string> //std::string
#include <vector> //std::vector
#include <sstream> //header providing string stream classes such as std::istringstream
#include <thread> //???
#include <chrono> //deals with time ie. measure time spans, specific points in time, real clocks 
#include "cpucon.h"

//Need to declare vectors of data type CPUdata to store CPU data fetched from /proc/stat, in Questionx.cpp
/*	std::vector<CPUData> snapshot1;
	std::vector<CPUData> snapshot2; */

//Defining function which reads CPU data from /proc/stat
//Objects kept in std::vector passed as parameter to function (since function passed pointer)
void Read::ReadCPUdata(std::vector<CPUData> & entries) {
	
	std::ifstream fileStat("/proc/stat"); //Opening /proc/stat for reading		
	std::string line; //declaring string to store line
	size_t counter = 0; //counter to stop reading after 5th line
 
	//reading lines 0-5 of /proc/stat
	while (counter < 5 && std::getline(fileStat, line)) {
		
		std::istringstream ss(line);
		
		//Creating extra element at end of vector entries (which points to parameter passed) with entry pointing to it
		entries.emplace_back(CPUData());
		CPUData & entry = entries.back();
		
		//storing 10 different state times from element 1-11 (so not to include CPU title)  
		for (size_t i = 1; i < 11; i++) {
			
			ss >> entry.times[i]; //entry points to last element of entries vector
		}
		
		counter++;
	}
}

//Defining function used in SaveCPUdata which calculates Idle time of CPU's based on CPU data fetched by ReadCPUdata. Takes in element of entries[i] of type CPUData and adds idle state times together.
size_t Save::TimeIdle(const CPUData & s) {

	size_t idle = s.times(S_IDLE) + s.times(S_IOWAIT);	
	return idle;
	
}

//Defining function used in SaveCPUdata which calculates active time of CPU's based on CPU data fetched by ReadCPUdata
size_t Save::TimeActive(const CPUData & s) {
	
	size_t active = s.times(S_USER) + s.times(S_NICE) + s.times(S_SYSTEM) + s.times(S_IRQ) + s.times(S_SOFTIRQ) + s.times(S_STEAL) + s.times(S_GUEST) + s.times(S_GUEST_NICE);
	return active;
}

//Defining function which calculates the active CPU time as a % of total CPU time ((active time)/(active time + idle time))
//Saves this iteratively to separate cpuanalysis.csv files for each CPU core and CPU total, along with total CPU time and number of iterations used in num solver 'n'
void Save::SaveCPUdata(const std::vector<CPUData> & snapshot1, const std::vector<CPUData> & snapshot2/*, const size_t n*/) {
		
	//Declaring constant stating size of snapshot, so that for loop can run through each element
	const size_t Num_of_Entries = snapshot1.size();	
	
	//Saving CPU consumption and CPU time for each core to different CPUanalysis(0-4).csv files. Where 0 is CPU total, 1 is CPU core 1, etc.
	const std::string cpuanalysis = "cpuanalysis";
	const std::string csv = ".csv";
	const std::string filename;
		
	//Running through each line of /proc/stat to find CPU consumption and total CPU time
	for (size_t i=0; i < Num_of_Entries; i++) {	
		
		//Declaring constant of type CPUdata to store element of vector<CPUData> entries[i]
		const CPUData & s1 = snapshot1;
		const CPUData & s2 = snapshot2;
			
		//Calculating active time, idle time, and total time of numerical solver, casting RHS as floats to match LHS
		const float ACTIVE_TIME = static_cast<float>(TimeActive(s1) - TimeActive(s2)); //difference in active time between each snapshot
		const float IDLE_TIME = static_cast<float>(TimeIdle(s1) - TimeIdle(s1)); //difference in idle time between each snapshot
		const float TOTAL_TIME = ACTIVE_TIME + TOTAL_TIME;
		
		//Calculating CPU Consumption by dividing active CPU time between snapshots by total CPU time between snapshots
		const float CPUConsumption = 100*(ACTIVE_TIME/TOTAL_TIME);
			
		//Using stringstream to create string that can be used to loop through different save files and pipe results
		std::stringstream ss;
		ss << i;
		file = cpuanalysis + ss.str() + csv;
			
		//Opening file
		std::ofstream file;
		file.open(file.c_str()); //.c_str() returns pointer to c-string representation of 'file' string object's value
			
		//Writing results into file	
		file << n ", " CPUConsumption ", " TOTAL_TIME << endl;

		//Closing file
		file.close();
	}
}	 
