#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>


class Image{

    public:

    //constructor
    Image(int, int);


    void circle(int, int, float, std::map<std::string,double>, std::map<std::string,bool>);
    void circle_alt(int, int, float, std::map<std::string,double>, std::map<std::string,bool>);

    void single_points(vector<tuple<int,int,double>>);


    std::vector<std::vector<double>> get_mesh();
    std::vector<std::vector<bool>> get_change_indices();

    private:


    std::vector<std::vector<double>> mesh;
    int rows, cols;


    std::vector<std::vector<bool>> change_indices;



};

