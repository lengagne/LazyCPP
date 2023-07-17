#include "LazyAdditionX.hpp"

LazyAdditionX::LazyAdditionX(std::list<LazyValue*>& a)
{
    type_ = LAZYADDITIONX;
    p_ = a;
    p_.sort();
    compute();
}

inline void LazyAdditionX::compute()
{
    value_ = 0;
    for (auto iter : p_)
        value_ += iter->value_;
}    

std::string LazyAdditionX::file_print( const std::string& varname)
{
    std::string cmd = varname+"["+ std::to_string(id_)+"] =";
    for (auto iter : p_)
        cmd += "+ " + iter->file_subname(varname) ;
    return   cmd;
}

void LazyAdditionX::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyAdditionX:("<<this<<"): AdditionX ("<<value_<<")"<<std::endl;
    for (auto iter : p_)
        iter->print(tab+"\t",index);
}   
    
void LazyAdditionX::print_equation()
{
    std::cout<<"(";
    for (auto iter : p_)
    {
        iter->print_equation();
        std::cout<<" PLUS ";   
    }
    std::cout<<0<<")";
}
