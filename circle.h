#include <iostream>
#include <cmath>
#include <vector>


class Grid{

    public:

    //constructor
    Grid(int, int);


    void circle(int, int, float, double, double, double, bool, bool, bool);

    std::vector<std::vector<double>> get_mesh();
    std::vector<std::vector<bool>> get_change_indices();

    private:


    std::vector<std::vector<double>>  mesh;
    std::vector<std::vector<bool>> change_indices;



};

