#include <iostream>
#include <eigen3/Eigen/Dense>

double df(double x, double y){// write your derivative here
    //return x + y; // example 1
    return y - 2 * x * x + 1; // example 2
}

double correct_slope(double x, double y, double predicted, double h,  double (*df)(double, double), double eps){
    double new_guess, old_guess;

    new_guess = predicted;
    old_guess = predicted - 10*eps;// just to prevent a random stop at the beginning

    while(abs(new_guess - old_guess)>eps){
        old_guess = new_guess;
        new_guess = y + .5 * h * (df(x, y) + df(x+h, old_guess));
    }
    return new_guess;
}

double mod_euler(double x, double y, double target_x, int n, double (*df)(double, double)){
    double h, predicted_point, eps;
    eps = 1e-8;
    h = (target_x - x) / n;// step size

    for(int i = 1; i <= n; i++){
        predicted_point = y + h * df(x, y);// == "normal" euler method

        predicted_point = correct_slope(x, y, predicted_point, h, df, eps);
        
        y = predicted_point;
        x +=h;

        std::cout << "predicted y at x = " << x << ": " << y << std::endl;
    }
    return y;
}

int main(){
    /*
    // example 1, solution should be about 1.4004
    double x = 0, y = 1, target_x = .3;
    int n = 3;//number of steps or division of range in n parts
    */

    // example 2 from https://www.geeksforgeeks.org/predictor-corrector-or-modified-euler-method-for-solving-differential-equation/
    // solution should be about 2.18147
    
    double x = 0, y = .5, target_x = 1;
    int n = 5;
    
    double sol = mod_euler(x, y, target_x, n,  df);
    std::cout << "the solution at "<< target_x <<" is: " << sol << std::endl;
    return 0;
}