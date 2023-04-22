
#include "LazySinus.hpp"

LazySinus::LazySinus(LazyValue* a)
{
    a_ = a;
    compute();
}
    
inline void LazySinus::compute()
{
    value_ = sin(a_->value_);
}
    

void LazySinus::print( const std::string& tab ,uint index) 
{
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";
    
    std::cout<<tab<<"("<<this<<"): SINUS ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
}

void LazySinus::print_equation()
{
    std::cout<<"sin(";
    a_->print_equation();
    std::cout<<")";
}
    
