#ifndef GUARD_RELAX
#define GUARD_RELAX

#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <string>


class Relax{

    public:

        //constructor
        Relax(std::vector<std::vector<double>>, std::vector<std::vector<bool>>);


        double getBestp();
        double relaxPotential(double, double, int);
        





    private:

        std::vector<std::vector<double>> mesh; 
        std::vector<std::vector<bool>> change_indices;

};








#endif
