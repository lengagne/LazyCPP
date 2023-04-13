#include <iostream>
#include "LazyCPP.hpp"


template<typename T>
T test_function( T& x, T& y)
{
//     T z = 42+ (x-2)*(x-2)    
//     T a = 42+ (x-2)*(x-2)*0.1;
//     T b = (x-2)*(x*y)*0.0 + x*y*1.5;
//     T z = a + b - y*y*1;
//     return z;
     return x+y-(x+y)*(x+y) *(x-y*y)*(x-y) ;

}

int main()
{
    std::cout<<"test of LazyCPP"<<std::endl;
    double x = 1.0;
    double y = 2.0;
    double z = test_function<double>(x,y);
    std::cout<<"z = "<< z <<std::endl<<std::endl;
    
    
    LazyInput lx(1.0,"X"), ly(2.0,"Y");
    LazyVariable X(lx), Y(ly);
    LazyVariable lz = test_function<LazyVariable>(X,Y);
    
    
    std::cout<<"X = "<< lx <<std::endl;
    std::cout<<"Y = "<< ly <<std::endl;
    std::cout<<"lz = " << lz <<std::endl<<std::endl;
    
    lx = -1.0;
    std::cout<<"X = "<< lx <<std::endl;
    std::cout<<"Y = "<< ly <<std::endl;    
    lz.evaluate();
    std::cout<<"lz = " << lz <<std::endl;
    
    
    GetLazyInfo();
    
    lz.print_graph();
    
    return 0;
}
