#include "LazyVariable.hpp"


LazyVariable::LazyVariable()
{
    ref_ = LMANAGER.get_zero();
}

LazyVariable::LazyVariable(const LazyVariable& a)
{
    ref_ = a.ref_;
}
    
LazyVariable::LazyVariable(const uint & a)
{
    ref_ = LMANAGER.add_constant(1.0*a);
}

LazyVariable::LazyVariable(const int & a)
{
    ref_ = LMANAGER.add_constant(1.0*a);
}
    
LazyVariable::LazyVariable(const double & a)
{
    ref_ = LMANAGER.add_constant(a);
}
    
LazyVariable::LazyVariable(const double &a, const std::string& name)
{
    ref_ = LMANAGER.add_input(a,name);
}
    
LazyVariable::LazyVariable(const std::string& name) 
{
    ref_ = LMANAGER.add_input(0,name);
}

void LazyVariable::operator = (double d)
{
    if (LMANAGER.is_input(ref_))
    {
        if (ref_->value_ != d)
        {
            ref_->set_time(LMANAGER.affect());
        }
        ref_->value_ = d;
    }else
        ref_ = LMANAGER.add_constant(d);
}
        
LazyVariable::~LazyVariable()
{
    
}
    
    
double LazyVariable::get_value() const
{
    return ref_->get_value();
}
    
bool LazyVariable::is_null() const
{
    return LMANAGER.is_zero(ref_);
}

/////////////////////////////////////////////////////
//////////////////// operators ////// ///////////////
/////////////////////////////////////////////////////
 
LazyVariable LazyVariable::operator + (const LazyVariable& b) const
{
    LazyVariable out( LMANAGER.add_additionX(ref_,b.ref_));
    return out;    
}

LazyVariable LazyVariable::operator - (const LazyVariable& b) const
{
    LazyVariable out( LMANAGER.add_soustraction(ref_, b.ref_));
    return out;    
}

LazyVariable LazyVariable::operator * (const LazyVariable& b) const
{
    LazyVariable out( LMANAGER.add_multiplicationX(ref_,b.ref_));
    return out;    
}

void LazyVariable::operator += (const LazyVariable& b)
{
    ref_ = LMANAGER.add_additionX(ref_,b.ref_);
}

void LazyVariable::operator -= (const LazyVariable& b)
{
    ref_ = LMANAGER.add_soustraction(ref_,b.ref_);
}

void LazyVariable::operator *= (const LazyVariable& b)
{
    ref_ = LMANAGER.add_multiplicationX(ref_,b.ref_);
}

std::ostream& operator<< (std::ostream& stream, const LazyVariable& v)
{
//     v.ref_->print_equation();
//     stream << v.ref_->value_;
    stream <<  v.ref_->get_string()<<"["<< v.ref_->id_<<"]";
    return stream;
}
   
    
bool LazyVariable::operator != (const LazyVariable& b) const
{
    return ref_ != b.ref_;
}

LazyVariable cos (const LazyVariable& a)
{
    LazyVariable out (LMANAGER.add_cosinus(a.ref_));
    return out;
}

LazyVariable sin (const LazyVariable& a)
{
    LazyVariable out (LMANAGER.add_sinus(a.ref_));
    return out;
}

bool operator==(const LazyVariable& a, double d)
{
    if (LMANAGER.is_constant(a.ref_) && a.ref_->value_ ==d)
        return true;
    return false;
}


/////////////////////////////////////////////////////
////////////////////Private functions ///////////////
/////////////////////////////////////////////////////


LazyVariable::LazyVariable(LazyValue* in):ref_(in)
{

}
