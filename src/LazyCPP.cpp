#include "LazyCPP.hpp"

LazyManager LMANAGER;


void LazyAddOutput(LazyVariable& in,uint index,uint rank)
{
    LMANAGER.add_output(in.ref_, index,rank);
}

void LazyGetInfo()
{
    LMANAGER.plot_info();
}

uint LazyGetNbInputs()
{
    return LMANAGER.get_nb_inputs();
}

bool LazyIsInput(const LazyVariable& in)
{
    return LMANAGER.is_input(in.ref_);
}

// uint LazyGetNbOutputs()
// {
//     return LMANAGER.get_nb_outputs();
// }

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

void LazyPrintOutputGraph(uint index, uint cpt)
{
    LMANAGER.print_output_graph(index,cpt);
}

void LazyReInit()
{
    LMANAGER.re_init_known();
}

void LazyReset()
{
    LMANAGER.reset();
}

double LazyUpdate(uint index, uint cpt)
{
    return LMANAGER.update(index,cpt);
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

// void LazyInput::operator = (const double & d)
// {
//     LMANAGER.affect_value(this,d);
// }

LazyVariable::LazyVariable()
{
    ref_ = LMANAGER.get_zero();       
}

LazyVariable::LazyVariable(const uint & a)
{
    ref_ = LMANAGER.add_constant(1.0*a);
//     if (a==0)
//         ref_ = LMANAGER.get_zero();
//     else
//         ref_ = new LazyConstant(1.0*a);        
}        

LazyVariable::LazyVariable(const int & a)
{
    ref_ = LMANAGER.add_constant(1.0*a);
//     if (a==0)
//         ref_ = LMANAGER.get_zero();
//     else    
//         ref_ = new LazyConstant(1.0*a);        
}    

LazyVariable::LazyVariable(const double & a)
{
    ref_ = LMANAGER.add_constant(a);    
//     if (a==0)
//         ref_ = LMANAGER.get_zero();
//     else
//         ref_ = new LazyConstant(a);        
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

LazyVariable& LazyVariable::operator - ( ) const
{
     LazyVariable *out = new LazyVariable();
    out->ref_ = LMANAGER.add_opposite(ref_);
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
    // si c'est une entrée on met à jour
    if( LMANAGER.is_input(ref_) )
    {
        ref_->value_  = val;
        return;
    }
    // sinon on considère comme une nouvelle constante
    ref_ = LMANAGER.add_constant(val);
}


// void LazyVariable::define_as_output(uint index)
// {
//     LMANAGER.add_output(index,ref_);
// }

bool LazyVariable::is_null() const
{
    return LMANAGER.is_zero(ref_);
}

LazyVariable cos (const LazyVariable&a)
{
    LazyVariable out;
    out.ref_ = LMANAGER.add_cosinus(a.ref_);
    return out;
}

LazyVariable sin (const LazyVariable&a)
{
    LazyVariable out;
    out.ref_ = LMANAGER.add_sinus(a.ref_);
    return out;    
}


        
