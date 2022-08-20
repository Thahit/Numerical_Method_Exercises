// also includes newton forward interpolation
// I am not a fan of methods that need the "target" to be in a certain range (in this case near the beginning of the sequence of x's)
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <math.h>

using std::cout;
using std::endl;

void forward_diff(const Eigen::MatrixXd& matr, const double target){
    int pos;
    double h, p, der1, sum;
    h = matr(1,0) - matr(0,0);

    //find first bigger x (I assume that the target is near the beginning of the inputs)
    for(int i = 0; i < matr.rows(); i++){
        if(target <= matr(i,0)){
            pos = i;
            break;
        }
    }

    p = (target - matr(pos,0)) / h;
    const int len = matr.rows()-pos;
    //this does seem to be the nicest way to get all the differences(diff is a pseudo 2 dim array)
    double diff [(matr.rows()-pos)*((matr.rows()-pos))] = { 0 };//init to 0
    //Eigen::Matrix<double, len, len> diff = Eigen::MatrixXd::Zero(len, len); //maybe an alternative

    for(int i = 0; i < matr.rows()-pos; i++){// init first row to the input values
        diff[i]=matr(pos+i, 1);
    }

    for(int i = 1; i < matr.rows()-pos; i++){// fill diff
        for(int j = 0; j<matr.rows()-pos-i; j++){
            diff[i*(matr.rows()-pos)+j]=diff[(i-1)*(matr.rows()-pos)+(j+1)]-diff[(i-1)*(matr.rows()-pos)+(j)];
        }
    }

    // if you want to check the array:
    /*
    for (int i = 0; i < matr.rows()-pos; i++){
        for(int j = 0; j<matr.rows()-pos-i; j++){
            cout << diff[j*(matr.rows()-pos)+i] << "\t";
        }
        cout <<endl;
    }
    */
    

    sum = 0;
    for(int i = 1; i < matr.rows()-pos; i++){
        //cout << (1.0/i) << "\t"<< diff[i*(matr.rows()-pos)] << "\t"<< pow(-1,i-1)<<endl;
        sum += ((1.0/i)* diff[i*(matr.rows()-pos)] * pow(-1,i-1));
    }
    der1 = sum/h;
    cout << "first derivative at the point "<< target << " is: " << der1 << endl;

    //2. der. would just be more of the same
}

int main(){
    double target = 1.1;
    Eigen::Matrix<double, 7, 2> m;
    m << 1, 7.989,
        1.1, 8.403,
        1.2, 8.781,
        1.3, 9.129, 
        1.4, 9.451,
        1.5, 9.750,
        1.6, 10.031;// example from book first derivative at 1.1 is 3.952 (the second is -3.74)

    forward_diff(m, target);
    
    return 0;
}