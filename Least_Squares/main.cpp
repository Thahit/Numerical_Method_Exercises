#include <iostream>
#include <eigen3/Eigen/Dense>
#include <tuple>
#include <math.h>
#include "gaussJordan.h"//for gaussian elimination

using std::cout;
using std::endl;

// gradient descent
std::tuple<double, double> descent(const Eigen::MatrixXd& matr, const double lr){// depends highly on lr
    double a, b, aNew, bNew, aError, bError, epsilon;
    a=2;
    b=0;
    int max_iter = 200'000;
    epsilon = 1e-8;
    
    for(int iter = 0; iter < max_iter; iter++){//should work
        aError = 0;
        bError = 0;
        for(int i =0; i < matr.rows(); i++){
            // need to look at the deriviatives to get the formulas (using MSE)
            aError -= 2*(matr(i,1) - (a*matr(i,0) + b))*matr(i,0);
            bError -= 2*(matr(i,1) - (a*matr(i,0) + b));
        }

        aError /= matr.rows();
        bError /= matr.rows();
        aNew -= aError*lr;
        bNew -= bError*lr;

        //cout << "a: " << aNew << "\tb: " << bNew << endl;//print iterations

        if (abs(aNew - a)<epsilon && abs(bNew - b) < epsilon){//changes small
            cout << "finished iterating" << endl << "number of iterations: " << iter << endl;
            break;
        }
        a=aNew;
        b=bNew;
    }
    cout << "a = " << a << endl << "b = " << b <<endl;
    return {a, b};
}

// momentum method
std::tuple<double, double> momentum(const Eigen::MatrixXd& matr){// seems to work
    double a,b, m1, m2, afactor1, afactor2, bfactor1, bfactor2;
    double shift = matr(1,0)- matr(0,0);// howw much the x increases at each step (1)
    // h=1 so can be ignored
    // the limits of the integrations are .5 and 100.5
    // lim.. ( a + bx ) dx  .5 to 100.5 =  from.. to ... ax+bx2/2= 100a +5050 b =m1
    // lim x( a + bx ) dx =ax^2/2 +bx^3/3 from... to ... =   5050 a + 338358 b
    
    afactor1=(matr(matr.rows()-1, 0)+shift/2) - (matr(0,0)-shift/2);
    bfactor1=pow(matr(matr.rows()-1, 0)+shift/2, 2)/2 - pow(matr(0,0)-shift/2, 2)/2;
    afactor2=pow(matr(matr.rows()-1, 0)+shift/2, 2)/2 - pow(matr(0,0)-shift/2, 2)/2;//same as above
    bfactor2=pow(matr(matr.rows()-1, 0)+shift/2, 3)/3 - pow(matr(0,0)-shift/2, 3)/3;

    m1 = shift * matr.col(1).sum();
    m2 = shift * matr.col(0).transpose() *matr.col(1);

    Eigen::Matrix<double, 2, 3> m;
    m << afactor1, bfactor1, m1,
        afactor2, bfactor2, m2;
    cout << m2 <<endl;
    Eigen::Matrix<double, 2, 3> res = gauss_elim(m);// as previously implemented
    a=res(0,2);
    b=res(1,2);
    
    //cout << "a: "<< a <<"\tb: "<<b <<endl;
    return {a, b};
}

int main(){
    const int num_points = 100;
    float noise, intercept, factor;
    intercept = -10;
    factor = 0.5;
    Eigen::Matrix<double, num_points, 2> m;
    m = Eigen::Matrix<double, num_points, 2>::Zero(num_points, 2);
    
    // there has to be a library for things like this, but I dont know it/them
    for(int i = 0; i<num_points; i++){// fill matrix with linear data + noise
        noise = (((float)rand()/RAND_MAX)-.5)*2; //from -1 to 1
        m(i,0) = i;
        m(i,1) = factor*i+noise+intercept;
        //cout << noise << endl; // print noise
    }
    
    //cout << "data: " << endl << m << endl;//print data

    // result should be about factor and intercept but with noise
    //momentum(m);

    descent(m, 0.0003);

    // maybe should be visualized
    return 0;
}