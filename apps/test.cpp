#include <iostream>
#include <math.h>
#include "LazyCPP.hpp"


template<typename T>
T test_function( T& x, T& y)
{
//      return (x+y)*(x*2)*(x+y+y+sin(y)+sin(y)+cos(x))-(x+y)*(x-y) *(y-(y*3)*y)*(x-y) * sin(y) + sin(y) * cos(y+x);
    return ((x*2)*(y*3)*cos(x)) + ((x*2)*(y*3)*cos(x)) + ((x*2)*(y*3)*cos(((x*2)*(y*3)*cos(x))));
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
    LazyVariable lz1 = lz*lz;
    LazyAddOutput(lz,0,0);
    LazyAddOutput(lz1,0,1);
    
    lz.print_equation();
    std::cout<<std::endl;
    LazyPrepare();
    
    std::cout<<"X = "<< x <<std::endl;
    std::cout<<"Y = "<< y <<std::endl;
    std::cout<<"lz = " << lz <<std::endl;
    std::cout<<"z = "<< test_function<double>(x,y) <<std::endl<<std::endl;
    //     PrintGraph(lz);
    
    X = x = -1.0;
    Y = y = 42.0;

    LazyUpdate(0,0);
    LazyUpdate(0,1);

    
//     LazyUpdateAll();
    std::cout<<"X = "<< X <<std::endl;
    std::cout<<"Y = "<< Y <<std::endl;        
    std::cout<<"lz = " << lz <<std::endl;
    std::cout<<"lz1 = " << lz1 <<std::endl;
    std::cout<<"z = "<< test_function<double>(x,y) <<std::endl<<std::endl;
    std::cout<<"z1 = "<< test_function<double>(x,y)*test_function<double>(x,y) <<std::endl<<std::endl;
//     
//     LazyGetInfo();
//     
// //     PrintGraph(lz);
    
    LazyPrintAllInputs();
    
    return 0;
}
