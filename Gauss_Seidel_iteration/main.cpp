// sometimes the 2, person is called Seidel and some other times Seidal
#include <iostream>
#include <eigen3/Eigen/Dense>

using std::cout;
using std::endl;

std::vector<double> gauss_seidel_it(const Eigen::MatrixXd& matr){
    // could also ask useer for epsilon/max iter, but I don't care
    double epsilon, max_error, res, aggr, approx[matr.rows()];
    std::vector<double> out;

    int max_iter = 10'000;// to avoid long waiting times

    epsilon = 1e-10;
    std::fill(approx, approx + matr.rows(), 0);// fill with 0s

    cout << "original matrix: " << endl << matr << endl;

    for(int i = 0; i < max_iter; i++){
        max_error = 0;

        // there might be a way to pre save the calculations with vectors etc., but...
        for(int y = 0; y < matr.rows(); y++){//iterate over equations
            aggr = 0;// here is the solution when inserting the other values into the equation

            for(int z = 0; z < matr.rows(); z++){// iterate over variables
                if(z!=y){
                    aggr += approx[z]*matr(y,z);
                }
            }

            res = (matr(y, matr.cols()-1) - aggr) / matr(y,y);//xi=(y-ax1-bx2..)/k
            //hopefully not 0, could check, but...
            cout <<res << endl;

            max_error = abs(res-approx[y]) > max_error ? abs(res-approx[y]) : max_error; // update max error if its bigger
            approx[y] = res;
        }

        if(max_error < epsilon){//stop
            cout << "number of iterations: " << i+1 << endl;
            break;
        }
    }
    
    cout << "The values of the variables are:" << endl;
    for(int i = 0; i < matr.rows(); i++){
        out.push_back((abs(approx[i]) > epsilon ? approx[i] : 0 ));
        cout << out[i] << endl;
    }
    return out;
}

int main(){
    Eigen::Matrix<double, 4, 5> m;
    m << 10, -2,-1, -1,
        3, -2, 10, -1,
        -1, 15, -1, -1,
        10, -2, 27, -1,
        -1, -2,10,-9;// 1,2,3,0

    gauss_seidel_it(m);



    return 0;
}