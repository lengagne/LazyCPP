
#include "LazySoustraction.hpp"

LazySoustraction::LazySoustraction(LazyValue* a, LazyValue* b) 
{
    type_ = LAZYSOUSTRACTION;
    a_ =a;
    b_ = b;
    value_ = a->value_-b->value_;        
}
    
inline void LazySoustraction::compute()
{
    value_ = a_->value_ - b_->value_;
}    

std::string LazySoustraction::file_print( const std::string& varname)
{
    return   varname+"["+ std::to_string(id_)+"] = " + a_->file_subname(varname) + "-" + b_->file_subname(varname);
}

    
void LazySoustraction::print( const std::string& tab ,uint index) 
{
    std::cout<<tab<<"LazySoustraction:("<<this<<") Soustraction ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
    b_->print(tab+"\t",index);
}
    
std::string LazySoustraction::get_string( )
{
    return "(" + a_->get_string() + "-" + b_->get_string() + ")";
}    
    
void LazySoustraction::print_equation()
{
    std::cout<<"(";
    a_->print_equation();
    std::cout<<" - ";
    b_->print_equation();
    std::cout<<")";
}
    
bool LazySoustraction::operator == (const LazyOperator2& A) const
{
    return (a_ == A.a_ && b_ == A.b_);
}    
    
