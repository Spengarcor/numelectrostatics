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
/*enum CPUstates {

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

};*/ //Why ;? 

//declaring structure of data type for our CPUdata objects
typedef struct CPUdata {
	std::string cpu; //to read CPU name
	size_t times[11]; //declaring array of size 11 to store CPU name and 10 CPU times

	//size_t is type able to represent largest size of any object in bytes, basically just unsigned (can never be negative) better version of signed (can be both positive and negative) int
} CPUdata;

//reads in CPU time at two snapshots from /proc/stat
struct Read {

	void ReadCPUdata(std::vector<CPUdata> & entries);

};

//saves CPU consumption and CPU time iteratively to CSV file for each number of iterations in numerical solver
struct Save {
		
	size_t TimeIdle(const CPUdata & e); 
	size_t TimeActive(const CPUdata & e);	
	
	void SaveCPUdata(const std::vector<CPUdata> & snapshot1, const std::vector<CPUdata> & snapshot2, const size_t n);	
};

#endif		
