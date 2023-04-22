
#include "LazyCosinus.hpp"

LazyCosinus::LazyCosinus(LazyValue* a)
{
    a_ = a;
    compute();
}
    
inline void LazyCosinus::compute()
{
    value_ = cos(a_->value_);
}
        
void LazyCosinus::print( const std::string& tab,uint index) 
{
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";
    
    std::cout<<tab<<"("<<this<<"): COSINUS ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
}

void LazyCosinus::print_equation()
{
    std::cout<<"cos(";
    a_->print_equation();
    std::cout<<")";      
}
