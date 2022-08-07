#include <iostream> //standard stuff
#include <iomanip> //for setw ...
#include <math.h>  // math stuff like cos
/* the function f contains example formulas, df its derivative.
Finding a root of Cos is interesting as it might find one that is very far away from the starting point
*/
float f(float x)
{
 //return x*log10(x)-1.2;
 return cos(x);
 //return tanh(x);
}
 float df(float x)
{
 //return log10(x) + 0.43429;
 return -sin(x);
 //return 1- pow(tanh(x),2);
}
int main()
{
 int itr, maxitr;
 float h, x0, x1, aerr;
 std::cout << "we are trying to approximate the/a root of the function f.\n" << 
 "Enter the first guess(x0), the allowed error, and the maximum allowed number of iterations (press enter between the inputs)" 
 << std::endl;
 std::cin >> x0 >> aerr >> maxitr;//ask for user input
 //std::cout << std::fixed; // used to set percision
 for (itr=1;itr<=maxitr;itr++)
 {
 h = f(x0)/df(x0);
 x1 = x0-h;
 std::cout << "Iteration no." << std::setw(3) << itr
 << "\tX = " << std::setw(9) //<< std::setprecision(6)
 << x1 << std::endl;
 if (fabs(h) < aerr)
 {
 std::cout << "After" << std::setw(3) << itr
 << " iterations, root = "
 << std::setw(3) << std::setprecision(6) << x1;
 return 0;
}
 x0 = x1;
}
std::cout << "Iterations not sufficient,"
 << "solution does not converge" << std::endl;
return 1;
}