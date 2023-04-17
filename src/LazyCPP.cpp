#include "LazyCPP.hpp"

LazyManager LMANAGER;

void AddLazyOutput(LazyVariable& in)
{
    LMANAGER.add_output(in.ref_);
}

void GetLazyInfo()
{
    std::cout<<"GetLazyInfo()"<<std::endl;
    std::cout<<"There are "<< LMANAGER.inputs_.size()<<" inputs."<<std::endl;
    std::cout<<"There are "<< LMANAGER.additions_.size()<<" additions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.soustractions_.size()<<" soustractions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.multiplications_.size()<<" multiplications."<<std::endl;
    std::cout<<"We performed "<< LMANAGER.nb_process_<<" evaluations."<<std::endl;
}

void LazyPrepare()
{
    LMANAGER.prepare();
    
}

void LazyUpdate(uint index)
{
    LMANAGER.update(index);
}

void LazyUpdateAll()
{
    LMANAGER.update_all();
}

void PrintGraph(LazyVariable& in)
{
    in.ref_->print("",LMANAGER.nb_process_);
}


LazyInput::LazyInput(double value, const std::string name):name_(name) 
{        
    value_ = value;
    known_ = true;
    LMANAGER.add_input(this);
}

void LazyInput::operator = (const double & d)
{
    LMANAGER.affect_value(this,d);
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

void LazyVariable::operator = (double val)
{    
    LMANAGER.affect_value( ref_,val);
}

double LazyVariable::evaluate()
{
    return LMANAGER.evaluate(*this);
}

void LazyVariable::define_as_output()
{
    LMANAGER.add_output(ref_);
}

        
