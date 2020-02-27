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
        void single_point(std::tuple<int,int,double>, bool);
        void rectangle(int, int, int, int, float); //refactor
        void circle(int, int, float, std::map<std::string,double>, std::map<std::string,bool>); //refactor


        //Relaxation methods
        double relaxPotential_J(int);
        double relaxPotential_GS(int);
        double relaxPotential_SOR(int);
        
        //Saving methods
        void save_to_csv(std::string);


    private:


        int rows, cols;
        std::vector<std::vector<double>> mesh;
        std::vector<std::vector<bool>> fixed_indices;

};

#endif
