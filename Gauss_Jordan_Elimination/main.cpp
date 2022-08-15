#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Dense>
#include "gaussJordan.h" // the functions are here

int main(){
    Eigen::Matrix<double, 4, 5> m;

    m << 11, 2, 3, 4,1,
        5, 6,7, 8, 1,
        9, 10, 1, 12,1,
        13, 14, 15 ,16,1;// solution = 0,-.5,0,.5

    Eigen::Matrix<double, 4, 5> res = gauss_elim(m);

    return 0;
}