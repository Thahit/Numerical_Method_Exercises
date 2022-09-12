#include <iostream>
#include <eigen3/Eigen/Dense>

void simplex(const Eigen::MatrixXd& to_max, const Eigen::MatrixXd& constraints){
    // create the simplex table
    const int len = to_max.cols()+2+constraints.rows();
    const int height = constraints.rows()+1;

    Eigen::MatrixXd table;
    table = Eigen::MatrixXd::Zero(height, len);

    //fill table
    // the code would be much nicer, if the max and constraints dont come in separately but I want it this way
    for(int i = 0; i < constraints.rows(); i++){// fill constraints
        int y;
        for (y = 0; y < constraints.cols()-1; y++){
            table(i,y) = constraints(i,y);
        }
        table(i,y+i) = 1;// set relevant basic var to 1
        table(i, len-1) = constraints(i, constraints.cols()-1);
    }

    for(int i = 0; i < to_max.cols(); i++){//fill max
        table(height-1, i) = -to_max(0,i);
    }
    table(height-1, len -2) = 1;
    //std::cout << table << std::endl;// print prepared table

    while(true){
        // find best variable to change
        int min_idx = 0;//col
        for(int i = 1; i < to_max.cols(); i++){//find min
            if(table(height-1, i)< table(height-1, min_idx))min_idx = i;
        }
        if(table(height-1, min_idx)>=0) break;

        int tightest_idx = 0;//row
        for(int i = 1; i < constraints.rows(); i++){//find best constraint to work with
            if(table(tightest_idx, len-1)/table(tightest_idx, min_idx) > table(i, len-1)/table(i, min_idx)){
                tightest_idx = i;
            }
        }
        
        table.row(tightest_idx) /=table(tightest_idx, min_idx);

        //row operations
        for(int i = 0; i < height; i++){
            if (i != tightest_idx){
                table.row(i) -=table.row(tightest_idx) / (table(tightest_idx, min_idx)/table(i, min_idx));
            }
        } 
    }
    std::cout << "inal table:" << std::endl << table << std::endl;//print  final table

    for(int i = 0; i < to_max.cols(); i++){//find basic variables
        //seems very inefficient
        int count_one = 0;
        int one_idx = 0;
        bool is_basic = true;
        for(int y = 0; y < height; y++){
            if(table(y,i)==1){
                count_one+=1;
                one_idx = y;
                if(count_one >1) is_basic=false;
            }
            else if (table(y,i)!=0){
                is_basic=false;
            }
        }
        if(is_basic){
            std::cout << "variable " << i << " is " << table(one_idx, len-1) << std::endl;
        }
    }
    std::cout << "The maximum reward is " << table(height-1, len-1) << std::endl;

}

int main(){
    // I am not sure what is the best way to initialize the problem as it consists of different things

    // need to manually change sizes when changing the problem

    //example 1 from    https://optimization.cbe.cornell.edu/index.php?title=Simplex_algorithm
    // solution = x1 = 0.4 x3=1.2 y=6.4
    Eigen::Matrix<double, 1, 3> to_maximize;
    to_maximize << 4,1,4;//== maximize 4x+1y+4z

    Eigen::Matrix<double, 3, 4> constraints;// unfortunately the constraints need to apready be in the "=" form not someting like "<=" because of the data structures
    constraints << 2,1,1,2, // == 2x+1y+z+s2=2
                    1,2,3,4,
                    2,2,1,8;
    
    /*
    //example 2 from  the book
    // solution = x2 = 42.22 x3=156.67 y=1066.67
    Eigen::Matrix<double, 1, 3> to_maximize;
    to_maximize << 4,3,6;

    Eigen::Matrix<double, 3, 4> constraints;
    constraints << 2,3,2,440, 
                    4,0,3,470,
                    2,5,0,430;
    */


    // implicit constr x,y,z,s1,s2,23 >=0

    simplex(to_maximize, constraints);


    return 0;
}