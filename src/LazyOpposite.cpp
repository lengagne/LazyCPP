#include "LazyOpposite.hpp"

LazyOpposite::LazyOpposite(LazyValue* a){
    a_ = a;
    value_ = -(a_->value_);
}
    
inline void LazyOpposite::compute()
{
    value_ = -(a_->value_);
}
    
void LazyOpposite::print( const std::string& tab ,uint index) 
{        
    std::cout<<tab<<"("<<this<<"): OPPOSITE ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
}

void LazyOpposite::print_equation()
{
    std::cout<<"(-";
    a_->print_equation();
    std::cout<<")";
}
    
