#include <iostream>
#include <eigen3/Eigen/Dense>

using std::cout;
using std::endl;

double power_method(const Eigen::MatrixXd& matr){
    double guess_value, epsilon, factor;
    Eigen::VectorXd stretch, guess_vector;
    int max_iter = 10'000;
    epsilon = 1e-10;
    guess_value =0;
    
    guess_vector=Eigen::VectorXd::Ones(matr.cols());// init to zero

    for(int iter = 0; iter < max_iter; iter ++){
        stretch = matr*guess_vector;
        factor =stretch[0];

        //finding the bigges absolute coefficient(there might be a built in thing,but I did not find it (only for non absolute values))
        for(int i=1; i<stretch.rows(); i++){
            if(abs(stretch[i])>abs(factor)){
                factor=stretch[i];
            }
        }

        stretch/=factor;
        //cout << stretch << endl;

        
        if(abs(factor-guess_value)<epsilon){
            cout << "number of iterations: " << iter << endl << "eigenvector:" 
            << endl <<"[" << guess_vector <<"}" << endl 
            << "eigenvalue: " << guess_value << endl;
            break;
        }
       guess_value = factor;
       guess_vector=stretch;
    }
    return guess_value;
}

int main(){
    Eigen::Matrix<double, 3, 3> m;
    /*
    m << 2, -1,0, 
        -1, 2, -1, 
        0, -1, 2;// eigenval = 3.41
    */
    m << 1, 2,0, 
        -2, 1, 2, 
        1, 3, 1;//eigenval = 3
    
    power_method(m);

    return 0;
}