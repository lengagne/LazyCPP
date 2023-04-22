#include <iostream>
#include <math.h>
#include "LazyCPP.hpp"


template<typename T>
T test_function( T& x, T& y)
{
     return (x+y); //-(x+y)*(x-y) *(y-y*y)*(x-y) * sin(y) + sin(y) * cos(y+x);
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
//     LazyVariable lz1 = lz*lz;
//     LazyAddOutput(lz,0,0);
//     LazyAddOutput(lz1,0,1);
//     
//     LazyPrepare();
//     
//     std::cout<<"X = "<< x <<std::endl;
//     std::cout<<"Y = "<< y <<std::endl;
    std::cout<<"lz = " << lz <<std::endl;
//     std::cout<<"z = "<< test_function<double>(x,y) <<std::endl;
//     std::cout<<"lz1 = " << lz1 <<std::endl<<std::endl;
//     //     PrintGraph(lz);
//     
//     X = x = -1.0;
//     std::cout<<"X = "<< X <<std::endl;
//     std::cout<<"Y = "<< Y <<std::endl;    
//     
// //     PrintGraph(lz);
// //     lz.evaluate();
//     LazyUpdateAll();
//     std::cout<<"lz = " << lz <<std::endl;
//     std::cout<<"z = "<< test_function<double>(x,y) <<std::endl;
//     
//     std::cout<<"lz1 = " << lz1 <<std::endl<<std::endl;
//     
//     LazyGetInfo();
//     
// //     PrintGraph(lz);
    
    return 0;
}
