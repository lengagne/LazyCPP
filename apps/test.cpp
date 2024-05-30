#include <iostream>
#include <math.h>
#include "LazyCPP.hpp"


template<typename T>
T test_function( T& x, T& y)
{
//      return (x+y)*(x*2)*(x+y+y+sin(y)+sin(y)+cos(x))-(x+y)*(x-y) *(y-(y*3)*y)*(x-y) * sin(y) + sin(y) * cos(y+x);
//     return ((x*2)*(y*3)*cos(x)) + ((x*2)*(y*3)*cos(x)) + ((x*2)*(y*3)*cos(((x*2)*(y*3)*cos(x))));
    
//     T a = 2*x;
//     T b = 2*y;
//     T c = 3; //*(x+y+2);
//     T d = c+c+c;
    
//     return a; //+(2*x)+(2*x)+a+a+a;
//     return a * b *c *d;
    
//     return sin(3.5*x) - cos(2*x*x + 2);
//     return cos(2.0+2*x);
//     return sin(2.0+2*x+5*3); // + 
    return sin(1*y-x+3*x+4*y+2.0);
    
//     return cos(x+y) * sin (x+y) + x+y;
}

int main()
{
    std::cout<<"test of LazyCPP"<<std::endl;
    double x = 1.0;
    double y = 2.0;
    double z = test_function<double>(x,y);
//     std::cout<<"z = "<< z <<std::endl<<std::endl;
    
    
    LazyVariable X(x,"X"), Y(y,"Y");
    
    LazyVariable lz = test_function<LazyVariable>(X,Y);
//     lz.print_detail();    
    
//     LazyVariable lz1 = lz+lz;
    
    std::cout<<"lz = "<< lz<<std::endl;
//     std::cout<<"lz1 = "<< lz1<<std::endl;
    LazyAddOutput(lz,0,0);
//     LazyAddOutput(lz1,1,0);
    
//     lz.print_equation();
//     std::cout<<std::endl;
    
    
    std::cout<<"Know LazyPrepare"<<std::endl;
    LazyPrepare("test");
    
//     X = x = -1.0;
//     Y = y = 42.0;
//     LazyUpdateInput();
//     LazyUpdateOutput(0,0);
    return 0;
}
