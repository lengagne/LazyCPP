#include "LazyMultiplicationX.hpp"

LazyMultiplicationX::LazyMultiplicationX(double d, std::list<LazyValue*>& a)
{
    constant_ = d;
    p_ = a;
    p_.sort();
    compute();
}

inline void LazyMultiplicationX::compute()
{
    value_ = constant_;
    for (auto iter : p_)
        value_ *= iter->value_;
}    

void LazyMultiplicationX::print( const std::string& tab,uint index) 
{
    
    std::cout<<tab<<"("<<this<<"): MultiplicationX ("<<value_<<")"<<std::endl;
    for (auto iter : p_)
        iter->print(tab+"\t",index);

}   
    
void LazyMultiplicationX::print_equation()
{
    std::cout<<"(";
    for (auto iter : p_)
    {
        iter->print_equation();
        std::cout<<" FOIS ";   
    }
    std::cout<<constant_<<")";
}
