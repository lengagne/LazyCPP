#include "LazyMultiplication.hpp"

LazyMultiplication::LazyMultiplication(LazyValue* a, LazyValue* b) 
{
    a_ = a;
    b_ = b;
    value_ = a->value_*b->value_;        
}
    
inline void LazyMultiplication::compute()
{
    value_ = a_->value_ * b_->value_;
}    
    
void LazyMultiplication::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"("<<this<<"): Multiplication ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
    b_->print(tab+"\t",index);
}   
    
void LazyMultiplication::print_equation()
{
    std::cout<<"(";
    a_->print_equation();
    std::cout<<"*";
    b_->print_equation();
    std::cout<<")";
}
    
