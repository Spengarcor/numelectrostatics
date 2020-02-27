//cpucon.h

//header file for cpucon.cpp declaring structures + functions for taking snapshots of numsolver CPU times and calculating CPU consumption

#ifndef CPUCON_H //including guad to ensure header file isnt inserted multiple times into a single .cpp file 
#define CPUCON_H

//including libraries which functions declared in structures will use

#include <fstream>
#include <iostream> //iostream class defined in fstream std::cout 
#include <string> //std::string
#include <vector> //std::vector
#include <sstream> //header providing string stream classes such as std::istringstream
#include <thread> //???
#include <chrono> //deals with time ie. measure time spans, specific points in time, real clocks   

//const int num_CPU_states = 10;

//Using enum to number each CPU state from 0-10 for easier referencing in functions
enum CPUStates {

        S_USER = 0,
        S_NICE,
        S_SYSTEM,
        S_IDLE,
        S_IOWAIT,
        S_IRQ,
        S_SOFTIRQ,
        S_STEAL,
        S_GUEST,
        S_GUEST_NICE

}; //Why ;?

//declaring structure of data type for our CPUdata objects
typedef struct CPUdata {
	std::string cpu; //to read string of CPU data from each line of /proc/stat
	size_t times[10/*num_CPU_states*/]; //declaring array of size 10 to store CPU state times of each CPU and total

	//size_t is type able to represent largest size of any object in bytes, basically just unsigned (can never be negative) better version of signed (can be both positive and negative) int
} CPUData;

//reads in CPU time at two snapshots from /proc/stat
struct Read {
	void ReadCPUdata(std::vector<CPUData> & entries);
};

//saves CPU consumption and CPU time iteratively to CSV file for each number of iterations in numerical solver
struct Save {
		
	size_t TimeIdle(const CPUData & e); 
	size_t TimeActive(const CPUData & e);	
	
	void SaveCPUdata(const std::vector<CPUData> & snapshot1, const std::vector<CPUData> & snapshot2/*, const size_t n*/);	
};

#endif		
