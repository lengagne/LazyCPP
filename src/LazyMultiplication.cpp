#include "LazyMultiplication.hpp"

LazyMultiplication::LazyMultiplication(LazyValue* a, LazyValue* b) 
{
    type_ = LAZYMULTIPLICATION;
//     if (a<b)
    if(compareLazyValue(a,b))
    {
        a_ = a;
        b_ = b; 
    }else
    {
        b_ = a;
        a_ = b;
    }
    value_ = a->value_*b->value_;        
}
    
inline void LazyMultiplication::compute()
{
    value_ = a_->value_ * b_->value_;
}    

std::string LazyMultiplication::file_print( const std::string& varname)
{
    return   varname+"["+ std::to_string(id_)+"] = " + a_->file_subname(varname) + "*" + b_->file_subname(varname);
}

std::string LazyMultiplication::get_string( )
{
    return "(" + a_->get_string() + "*" + b_->get_string() + ")";
}
    
void LazyMultiplication::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyMultiplication:("<<this<<"): Multiplication ("<<value_<<")"<<std::endl;
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
    
