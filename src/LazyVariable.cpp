#include "LazyVariable.hpp"


LazyVariable::LazyVariable()
{
    ref_ = LMANAGER.get_zero();
}

LazyVariable::LazyVariable(const LazyVariable& a)//:ref_(a.ref_)
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
        
LazyVariable::~LazyVariable(){}
    
    
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

std::ostream& operator<< (std::ostream& stream, const LazyVariable& v)
{
    std::cout<<"pointeur = "<< v.ref_<<std::endl;
    std::cout<<"equation = ";    v.ref_->print_equation();
    return stream;
}
   
    
bool LazyVariable::operator != (const LazyVariable& b) const
{
    return ref_ != b.ref_;
}


/////////////////////////////////////////////////////
////////////////////Private functions ///////////////
/////////////////////////////////////////////////////


LazyVariable::LazyVariable(LazyValue* in):ref_(in)
{
    std::cout<<"Constructor a partir de pointeur"<<std::endl;
    ref_->print_equation();
    std::cout<<"Constructor a partir de pointeur"<<std::endl;
    std::cout<<" moi meme = "<< *this <<std::endl;
}
