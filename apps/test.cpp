#include <iostream>
#include <math.h>
#include "LazyCPP.hpp"


template<typename T>
T test_function( T& x, T& y)
{
//      return (x+y)*(x*2)*(x+y+y+sin(y)+sin(y)+cos(x))-(x+y)*(x-y) *(y-(y*3)*y)*(x-y) * sin(y) + sin(y) * cos(y+x);
//     return ((x*2)*(y*3)*cos(x)) + ((x*2)*(y*3)*cos(x)) + ((x*2)*(y*3)*cos(((x*2)*(y*3)*cos(x))));
    
    T a = 2*x;
    T b = 2*y;
    T c = 3; //*(x+y+2);
    T d = c+c+c;
    
//     return a; //+(2*x)+(2*x)+a+a+a;
//     return a * b *c *d;
    
    return cos(x) - x;
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
    
    lz.print_equation();
    std::cout<<std::endl;
    
    LazyPrepare("test");
    
//     std::cout<<"X = "<< x <<std::endl;
//     std::cout<<"Y = "<< y <<std::endl;
//     std::cout<<"lz = " << lz <<std::endl;
//     std::cout<<"z = "<< test_function<double>(x,y) <<std::endl<<std::endl;
    //     PrintGraph(lz);
    
    X = x = -1.0;
    Y = y = 42.0;

    LazyUpdateInput();
    LazyUpdateOutput(0,0);
//     LazyUpdate(0,1);
    
//     std::cout<<"X = "<< X <<std::endl;
//     std::cout<<"Y = "<< Y <<std::endl;        
//     std::cout<<"lz = " << lz <<std::endl;
//     std::cout<<"lz1 = " << lz1 <<std::endl;
//     std::cout<<"z = "<< test_function<double>(x,y) <<std::endl<<std::endl;
//     std::cout<<"z1 = "<< test_function<double>(x,y)*test_function<double>(x,y) <<std::endl<<std::endl;

//     LazyPrintAllInputs();
    
    
    return 0;
}
