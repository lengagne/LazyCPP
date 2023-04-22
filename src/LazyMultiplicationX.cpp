#include "LazyMultiplicationX.hpp"

LazyMultiplicationX::LazyMultiplicationX(std::list<LazyValue*>& a)
{
    p_ = a;
    p_.sort();
    compute();
}

inline void LazyMultiplicationX::compute()
{
    value_ = 1.0;
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
    std::cout<<1<<")";
}
