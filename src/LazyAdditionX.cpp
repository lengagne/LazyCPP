#include "LazyAdditionX.hpp"

LazyAdditionX::LazyAdditionX(double d, std::list<LazyValue*>& a)
{
    constant_ = d;
    p_ = a;
    p_.sort();
    compute();
}

inline void LazyAdditionX::compute()
{
    value_ = constant_;
    for (auto iter : p_)
    {
        value_ += iter->value_;
    }
}    

void LazyAdditionX::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"("<<this<<"): AdditionX ("<<value_<<")"<<std::endl;
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
    std::cout<<constant_<<")";
}
