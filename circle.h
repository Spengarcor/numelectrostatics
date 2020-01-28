#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>


class Grid{

    public:

    //constructor
    Grid(int, int);


    void circle(int, int, float, std::map<std::string,double>, std::map<std::string,bool>);

    std::vector<std::vector<double>> get_mesh();
    std::vector<std::vector<bool>> get_change_indices();

    private:


    std::vector<std::vector<double>>  mesh;
    std::vector<std::vector<bool>> change_indices;



};

