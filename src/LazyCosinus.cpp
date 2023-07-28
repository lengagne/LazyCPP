
#include "LazyCosinus.hpp"

LazyCosinus::LazyCosinus(LazyValue* a)
{
    type_ = LAZYCOSINUS;
    a_ = a;
    compute();
}
    
inline void LazyCosinus::compute()
{
    value_ = cos(a_->value_);
}

std::string LazyCosinus::file_print( const std::string& varname)
{
    return varname+"["+ std::to_string(id_)+"] = cos(" + a_->file_subname(varname) + ")";
}

std::string LazyCosinus::get_string( )
{
    return "cos(" + a_->get_string() + ")";
}
        
void LazyCosinus::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyCosinus:("<<this<<"): COSINUS ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
}

void LazyCosinus::print_equation()
{
    std::cout<<"cos(";
    a_->print_equation();
    std::cout<<")";      
}
