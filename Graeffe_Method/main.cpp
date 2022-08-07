// (there is no example program for this method in the book)
#include <iostream> //standard stuff
#include <math.h>  // math stuff like cos
float poly(float x, float a, float b, float c, float d)
/**
 * calculates the y of the (third degree) polynomial of the given x
 * 
 * @param x desired position
 * @param a a*x^3
 * @param b b*x^2
 * @param c c*x
 * @param d +d
 * @return y = output of the polynomial
 */
{
    return a*pow(x,3)+b*pow(x,2)+c*x+d;
}
int main()
{
 int power;
 float a,b,c,d;
 double a2,b2,c2,d2,a3,b3,c3,d3;

 // this part is for when you want to do it with user input
 /*
 std::cout << "we are trying to find the roots of your polynomial.\n" << 
 "Pease enter one after another the values of a,b,c and d of the polynomial ax^3+bx^2+cx^1+d (this method also works for more terms) (large numbers might cause an overflow) \n(press enter between the inputs)" 
 << std::endl;
 std::cin >> a >> b >> c >> d;//ask for user input
 //std::cout << std::fixed; // used to set percision
 std::cout <<"now enter the shquaring factor 2^m" 
 << std::endl;
 std::cin >> power;
 */
 //a=1,b=-2,c=-5,d=6;// roots =3,-2,1
 a=7,b=13,c=0,d=-2;//roots = -1.7655, -.45072, .35906
 a2=a, b2=b, c2=c, d2=d;
 power=8;

 for(int i=0; i<power;i++)
 {
    //these factors have been figuerd out by hand by me
    a3=a2, b3=b2, c3=c2, d3=d2;//temp values

    a2 = pow(a3,2);
    b2 = (-2*a3*c3 + pow(b3,2));
    c2 = (-2*b3*d3 + pow(c3,2));
    d2 = pow(d3,2);
    //std::cout << a2 <<"\t"<<-b2<<"\t"<<c2 <<"\t"<<-d2<<std::endl;
 }
 
 double factors[4]={a2, -b2, c2, -d2};//could have done this from the start but....
 float roots[3];
 double bracket_sum,bracket_sum2,bracket_sum3;
 // I don't see a smart way to program this, because the number of for loops seems to depend on the polynomial

 //find factor 1(biggest)
 bracket_sum=factors[1]/factors[0];
 roots[0]=pow(10, log10(abs(bracket_sum))/pow(2,power));
 //2. factor
 bracket_sum2=factors[2]/factors[0];
 roots[1]=pow(10, log10(abs(bracket_sum2/bracket_sum))/pow(2,power));

 //3. factor
 bracket_sum3=factors[3]/factors[0];
 roots[2]=pow(10, log10(abs(bracket_sum3/bracket_sum2))/pow(2,power));
 std::cout <<"absolute value of the roots;"<<"\t"<<roots[0]<<"\t"<<roots[1]<<"\t"<< roots[2]<<std::endl;

 // to get the value of the roots with the sign
 // does not work if a root appears 2. (e.b. 12 and -2 are roots)
 // I am fine with this but smarter ways to get the signs exist
 for(int i=0;i<3;i++){
    if(abs(poly(-roots[i],a,b,c,d))<abs(poly(roots[i],a,b,c,d))){
        roots[i]*=-1;
    }
 }
 std::cout <<"value of the roots;"<<"\t"<<roots[0]<<"\t"<<roots[1]<<"\t"<< roots[2];

return 0;
}