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
        double relaxPotential_J(double, int, bool);
        double relaxPotential_GS(double, int, bool);
        double relaxPotential_SOR(double, int, bool);
        
        //Interpolation
        double lagInterpolate(int, int, int, int);        
        double lagInterpolate2(int, int, int, int);

        //Saving methods
        void save_to_csv(std::string);
        void save_errors(int, double, double);

        //error analysis
        std::vector<std::vector<double>> analQ1(int rows,int cols,double V,double r1,double r2, int c_x,int c_y);
        std::vector<std::vector<double>> analQ2(int rows,int cols,double V, double r,int c_x,int c_y, int x_min,int x_max);

        double get_abs_error(int rows, int cols, std::vector<std::vector<double>> A, std::vector<std::vector<double>> B);

        std::vector<std::vector<double>> mesh;

    private:


        int rows, cols;
        std::vector<std::vector<bool>> fixed_indices;

};

#endif
