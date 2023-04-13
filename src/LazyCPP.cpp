#include "LazyCPP.hpp"

LazyManager LMANAGER;

void GetLazyInfo()
{
    std::cout<<"GetLazyInfo()"<<std::endl;
    std::cout<<"There are "<< LMANAGER.inputs_.size()<<" inputs."<<std::endl;
    std::cout<<"There are "<< LMANAGER.additions_.size()<<" additions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.soustractions_.size()<<" soustractions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.multiplications_.size()<<" multiplications."<<std::endl;
}


LazyInput::LazyInput(double value, const std::string name):name_(name) 
{        
    value_ = value;
    LMANAGER.add_input(this);
}


LazyVariable& LazyVariable::operator + (LazyVariable& b)
{
    LazyVariable *out = new LazyVariable();
    out->ref_ = LMANAGER.add_addition(ref_,b.ref_);
    return *out;
}

LazyVariable& LazyVariable::operator - (LazyVariable& b)
{
    LazyVariable *out = new LazyVariable();
    out->ref_ = LMANAGER.add_soustraction(ref_,b.ref_);
    return *out;
}

LazyVariable& LazyVariable::operator * (LazyVariable& b)
{
    LazyVariable *out = new LazyVariable();
    out->ref_ = LMANAGER.add_multiplication(ref_,b.ref_);
    return *out;
}


        
