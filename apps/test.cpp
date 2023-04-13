#include <iostream>
#include "LazyCPP.hpp"


template<typename T>
T test_function( T& x, T& y)
{
     return (x+y)-(x+y)*(x-y) *(y-y*y)*(x-y) ;
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
//     PrintGraph(lz);
    
    x = -1.0;
    lx = x;
    std::cout<<"X = "<< lx <<std::endl;
    std::cout<<"Y = "<< ly <<std::endl;    
    
//     PrintGraph(lz);
    lz.evaluate();
    std::cout<<"lz = " << lz <<std::endl;
    std::cout<<"z = "<< test_function<double>(x,y) <<std::endl<<std::endl;
    
    GetLazyInfo();
    
//     PrintGraph(lz);
    
    return 0;
}
