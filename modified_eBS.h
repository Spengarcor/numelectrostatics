#ifndef GUARD_EBOUNDARY
#define GUARD_EBOUNDARY

#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <map>
#include <string>
#include <tuple>
#include <fstream>

class eBoundarySolver{

    public:

        //constructor
        eBoundarySolver(int, int);

        //Boundary condition drawing methods
        void single_point(std::tuple<int,int,double>, int);
        void rectangle(int, int, int, int, float); //refactor
        void circle(int, int, double, double, double, double); //refactor
	void change_boundary(int, int, int, double, double);

        //Relaxation methods
        double relaxPotential_J(double, int);
        double relaxPotential_GS(double, int);
        double relaxPotential_SOR(double, int);
        
        //Saving methods
        void save_to_csv(std::string);


    private:


        int rows, cols;
        std::vector<std::vector<double>> mesh;
        std::vector<std::vector<int>> fixed_indices;
	std::vector<std::vector<std::vector<double>>> boundaries;
};

#endif
