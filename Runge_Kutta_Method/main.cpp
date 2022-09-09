// I will be using a fourth order RK method
#include <iostream>

double df(double x, double y){// write your derivative here
    return x + y*y; // example 1
}

double RungeKutta4(double x, double y, double target_x, int n, double (*df)(double, double)){
    double h, k1, k2, k3, k4;
    h = (target_x - x) / n;// step size

    for(int i = 1; i <= n; i++){
        k1 = df(x,y);
        k2 = df(x+h/2, y+h*k1/2);
        k3 = df(x+h/2, y+h*k2/2);
        k4 = df(x+h, y+h*k3);
        
        y += h*(k1 + 2*(k2 + k3) + k4)/6;
        x += h;

        std::cout << "predicted y at x = " << x << ": " << y << std::endl;
    }
    return y;
}

int main(){
    
    // example 1, solution should be about 1.2736
    double x = 0, y = 1, target_x = .2;
    int n = 2;//number of steps or division of range in n parts
    
    double sol = RungeKutta4(x, y, target_x, n,  df);
    std::cout << "the solution at "<< target_x <<" is: " << sol << std::endl;
    return 0;
}