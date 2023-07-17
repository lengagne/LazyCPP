
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

        
void LazyCosinus::print( const std::string& tab,uint index) 
{
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";
    
    std::cout<<tab<<"LazyCosinus:("<<this<<"): COSINUS ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
}

void LazyCosinus::print_equation()
{
    std::cout<<"cos(";
    a_->print_equation();
    std::cout<<")";      
}
