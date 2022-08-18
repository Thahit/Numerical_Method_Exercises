#include <iostream>
#include <eigen3/Eigen/Dense>
#include <math.h>

double lagr_interp(const Eigen::MatrixXd& matr, const double target){
    double intermediate, guess; // guess starts at 0 implicitly

    for(int i = 0; i < matr.rows(); i++){// iterate over polynomial terms
        intermediate = matr(i, 1);
        for(int y = 0; y < matr.rows(); y++){
            if (y != i){
                intermediate *= (target - matr(y,0)) / (matr(i,0) - matr(y,0));
            }
        }
        guess += intermediate;
    }
    std::cout << "estimated value for " << target << ": " << guess << std::endl;
    return guess;
}

int main(){
    double target = 3.141159;
    Eigen::Matrix<double, 5, 2> m;// examples
    m << 2.1, sqrt(2.1),
        2.5, sqrt(2.5),
        3, sqrt(3),
        3.2, sqrt(3.2), 
        3.61, sqrt(3.61);// 3.14159 = 1.77245310234
    /*
    m << 5, 150,
        7, 392,
        11, 1452,
        13, 2366,
        17, 5202;// target 9, solution 810  (example from book)
    */
    
    lagr_interp(m, target);
    return 0;
}