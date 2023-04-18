#include "LazyCPP.hpp"

LazyManager LMANAGER;


void LazyAddOutput(LazyVariable& in)
{
    LMANAGER.add_output(in.ref_);
}

void LazyGetInfo()
{
    std::cout<<"GetLazyInfo()"<<std::endl;
    std::cout<<"There are "<< LMANAGER.inputs_.size()<<" inputs."<<std::endl;
    std::cout<<"There are "<< LMANAGER.additions_.size()<<" additions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.soustractions_.size()<<" soustractions."<<std::endl;
    std::cout<<"There are "<< LMANAGER.multiplications_.size()<<" multiplications."<<std::endl;
//     std::cout<<"We performed "<< LMANAGER.nb_process_<<" evaluations."<<std::endl;
}

uint LazyGetNbInputs()
{
    return LMANAGER.get_nb_inputs();
}

uint LazyGetNbOutputs()
{
    return LMANAGER.get_nb_outputs();
}

// bool LazyIsZero(LazyValue * in)
// {
//     return LMANAGER.is_zero(in);
// }

void LazyPrepare()
{
    LMANAGER.prepare();
}

void LazyPrintGraph(LazyVariable& in)
{
    in.ref_->print("");
}

void LazyPrintInputs()
{
    LMANAGER.print_inputs();
}

void LazyReInit()
{
    LMANAGER.re_init_known();
}

void LazyReset()
{
    LMANAGER.reset();
}

double LazyUpdate(uint index)
{
    return LMANAGER.update(index);
}

void LazyUpdateAll()
{
    LMANAGER.update_all();
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

LazyVariable::LazyVariable()
{
    /*ref_ = LMANAGER.get_zero();   */     
    ref_ = new LazyConstant(0.0);
}

LazyVariable::LazyVariable(const uint & a)
{
//     if (a==0)
//         ref_ = LMANAGER.get_zero();
//     else
        ref_ = new LazyConstant(1.0*a);        
}        

LazyVariable::LazyVariable(const int & a)
{
/*    if (a==0)
        ref_ = LMANAGER.get_zero();
    else   */ 
        ref_ = new LazyConstant(1.0*a);        
}    

LazyVariable::LazyVariable(const double & a)
{
//     if (a==0)
//         ref_ = LMANAGER.get_zero();
//     else
        ref_ = new LazyConstant(a);        
}    
    

LazyVariable& LazyVariable::operator + (const LazyVariable& b) const
{
    LazyVariable *out = new LazyVariable();
    out->ref_ = LMANAGER.add_addition(ref_,b.ref_);
    return *out;
}

LazyVariable& LazyVariable::operator - (const LazyVariable& b) const
{
    LazyVariable *out = new LazyVariable();
    out->ref_ = LMANAGER.add_soustraction(ref_,b.ref_);
    return *out;
}

LazyVariable& LazyVariable::operator * (const LazyVariable& b) const
{
    LazyVariable *out = new LazyVariable();
    out->ref_ = LMANAGER.add_multiplication(ref_,b.ref_);
    return *out;
}

void LazyVariable::operator += (const LazyVariable& b)
{
//     *this =  *this - b;
    ref_ = LMANAGER.add_addition(ref_,b.ref_);
}

void LazyVariable::operator -= (const LazyVariable& b)
{
//     *this =  *this - b;
    ref_ = LMANAGER.add_soustraction(ref_,b.ref_);
}

void LazyVariable::operator *= (const LazyVariable& b)
{
    ref_ = LMANAGER.add_multiplication(ref_,b.ref_);
}


void LazyVariable::operator = (double val)
{    
    LMANAGER.affect_value( ref_,val);
}

// double LazyVariable::evaluate()
// {
//     return LMANAGER.evaluate(*this);
// }

void LazyVariable::define_as_output()
{
    LMANAGER.add_output(ref_);
}

// bool LazyVariable::is_not_null() const
// {
//     return ! LMANAGER.is_zero(ref_);
// }

LazyVariable cos (const LazyVariable&a)
{
    LazyVariable out;
    out.ref_ = new LazyCosinus(a.ref_);
    return out;
}

LazyVariable sin (const LazyVariable&a)
{
    LazyVariable out;
    out.ref_ = new LazySinus(a.ref_);
    return out;    
}


        
