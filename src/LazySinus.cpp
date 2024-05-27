
#include "LazySinus.hpp"

LazySinus::LazySinus(LazyValue* a)
{
    type_ = LAZYSINUS;
    a_ = a;
    compute();
}
    
inline void LazySinus::compute()
{
    value_ = sin(a_->value_);
}

std::string LazySinus::file_print( const std::string& varname)
{
    return varname+"["+ std::to_string(id_)+"] = sin(" + a_->file_subname(varname) + ")";
}

std::string LazySinus::get_string( )
{
    return "sin(" + a_->get_string() + ")";
}

void LazySinus::print( const std::string& tab ,uint index) 
{
    std::cout<<tab<<"LazySinus:("<<this<<"): SINUS ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
}

void LazySinus::print_equation()
{
    std::cout<<"sin(";
    a_->print_equation();
    std::cout<<")";
}
    
