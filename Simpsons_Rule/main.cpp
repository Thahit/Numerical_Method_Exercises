// using simpsons 1/3 Rule
// all these 1/3, 3/8, Trapezoid etc. rules are not very interesting to program
#include <iostream>
#include <eigen3/Eigen/Dense>

using std::cout;
using std::endl;

double simpson_integr(const Eigen::MatrixXd& matr){// 1/3 rule
    double guess, h;
    h = matr(1,0) - matr(0,0);
    guess = h/3*(matr(0,1) + 4*matr(1,1)+matr(2,1));

    cout << "The integral of your function between " << matr(0,0) << " and " << matr(matr.rows()-1,0) << " is: " << guess << endl;

    return guess;
}

int main(){
    Eigen::Matrix<double, 3, 2> m;
    
    m << 0, sin(0), 
        M_PI/4, sin(M_PI/4),
        M_PI/2, sin(M_PI/2);// integral = 1
    
    simpson_integr(m);

    return 0;
}