#ifndef GAUSSJORDANELIM_H
#define GAUSSJORDANELIM_H
// not sure if this is fine like this, but works for mow
#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Dense>

void forward_step(Eigen::MatrixXd& matr, int epsilon){
    // I am assuming the system has no free variables as I am too lazy to be more robust
    int max_idx;
    double max_val, factor;
    
    for(int i = 0; i< matr.rows(); i++){
        // find the element with the biggest value(only in column no partial pivoting)
        // there is a built in function which does that too, but that would make things to easy
        max_idx = i;
        max_val = matr(i,i);
        
        for(int y = i+1; y< matr.rows();y++){
            if (abs(max_val)<abs(matr(y,i))){
                max_idx = y;
                max_val = matr(y,i);
            }
        }
        //now swap the columns
        if(i != max_idx){
            matr.row(i).swap(matr.row(max_idx));
        }
        // make the rows below 0
        for(int y = i+1; y< matr.rows();y++){
            if (abs(matr(y,i)) > epsilon){//to avoid some explosions
                factor = matr(y,i)/max_val;
                matr.row(y) -= matr.row(i)*factor;
            }
            matr(y,i)=0;
        }
    }
}

void backward_step(Eigen::MatrixXd& matr, int epsilon){
    // I am assuming the system has no free variables as I am too lazy to be more robust
    double factor;
    
    for(int i = matr.rows()-1; i > -1; i--){
        // make everything above 0
        
        for(int y = 0; y < i; y++){
            
            if(abs(matr(y,i)) > epsilon){//to avoid some explosions
                factor = matr(y,i)/matr(i,i);
                matr.row(y)-= factor*matr.row(i);
            }
            //matr(y,i) = 0; // could do for safety/style, but seems so be good enough
        }
        // make variable 1
        matr.row(i) /= matr(i,i);
        

    }
}

Eigen::MatrixXd gauss_elim(const Eigen::MatrixXd& matr){
    Eigen::MatrixXd out;
    double epsilon = .000001;
    out = matr;
    std::cout << "original matrix: " << std::endl << matr << std::endl;

    forward_step(out, epsilon);
    //std::cout<< "intermediate matrix: "<<std::endl<<out <<std::endl;

    // we could do some checking now if everything is solvable but I assume they are
    backward_step(out, epsilon);
    std::cout << "edited matrix: " << std::endl << out << std::endl;
    
    std::cout << "The values of the variables are:" << std::endl;
    for(int i = 0; i < out.rows(); i++){
        std::cout << (abs(out(i, out.cols()-1)) > epsilon ? out(i, out.cols()-1) : 0 ) << std::endl;
    }
    return out;
}
#endif