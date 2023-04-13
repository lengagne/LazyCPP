#include <iostream>
#include "LazyCPP.hpp"


template<typename T>
T test_function( T& x, T& y)
{
//     T z = 42+ (x-2)*(x-2)    
    T a = 42+ (x-2)*(x-2)*0.1;
    T b = (x-2)*(x*y)*0.0 + x*y*1.5;
    T z = a + b - y*y*1;
    return z;
}

int main()
{
    std::cout<<"test of LazyCPP"<<std::endl;
    double x = 1.0;
    double y = 2.0;
    double z = test_function<double>(x,y);
    std::cout<<"z = "<< z <<std::endl;
    
    LazyInput lx = 1.0, ly = 2.0;
    LazyVariable X(lx), Y(ly);
    LazyVariable lz = test_function<LazyVariable>(X,Y);
    
    std::cout<<"lz = " << *(lz.ref_) <<std::endl;
    
    lx = -1.0;
    lz.evaluate();
    std::cout<<"lz = " << *(lz.ref_) <<std::endl;
    
    return 0;
}
