#include "LazyCPP.hpp"

LazyManager LMANAGER;


void LazyManager::add_input( LazyInput* in)
{
    inputs_.push_back(in);
}

LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
{
    LazyAddition* out = new LazyAddition(a,b);
    additions_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_multiplication( LazyValue* a , LazyValue *b)
{
    LazyMultiplication* out = new LazyMultiplication(a,b);
    multiplications_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_soustraction( LazyValue* a , LazyValue *b)
{
    LazySoustraction* out = new LazySoustraction(a,b);
    soustractions_.push_back(out);
    return out;
}

void GetLazyInfo()
{
    std::cout<<"GetLazyInfo()"<<std::endl;
    std::cout<<"There are "<< LMANAGER.inputs_.size()<<" inputs."<<std::endl;
    std::cout<<"There are "<< LMANAGER.additions_.size()<<" additions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.soustractions_.size()<<" soustractions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.multiplications_.size()<<" multiplications."<<std::endl;
}

LazyInput::LazyInput(double value) 
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


        
