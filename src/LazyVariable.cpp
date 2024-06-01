#include "LazyVariable.hpp"

LazyVariable::LazyVariable()
{
    parser_ = LMANAGER.add_constant_parser(0.0);
    creator_ = nullptr;
}

LazyVariable::LazyVariable(LazyParser* in)
{
    parser_ = in ;
    creator_ = nullptr;
}

LazyVariable::LazyVariable(const LazyVariable& a)
{
    parser_ = a.parser_;
    creator_ = a.creator_;
}

void LazyVariable::operator = (const LazyVariable& a)
{
    parser_ = a.parser_;
    creator_ = a.creator_;
}
    
LazyVariable::LazyVariable(const uint & a)
{
    parser_ = LMANAGER.add_constant_parser(1.0*a);
    creator_ = nullptr;
}

LazyVariable::LazyVariable(const int & a)
{
    parser_ = LMANAGER.add_constant_parser(1.0*a);
    creator_ = nullptr;
}
    
LazyVariable::LazyVariable(const double & a)
{
    parser_ = LMANAGER.add_constant_parser(a);
    creator_ = nullptr;
}
    
// create an input
LazyVariable::LazyVariable(const double &a, const std::string& name)
{
    parser_ = LMANAGER.add_input(a,name);
    creator_ = parser_->explose();
}

// create an input
LazyVariable::LazyVariable(const std::string& name) 
{
    parser_ = LMANAGER.add_input(0,name);
    creator_ = parser_->explose();
}

void LazyVariable::operator = (double d)
{
    if (parser_ == nullptr || LMANAGER.is_zero(parser_))
    {
        parser_ = LMANAGER.add_constant_parser(d);
    }else
    if (parser_->typep_ == LAZYP_INPUT)
    {
        ((LazyInput*) parser_)->value_ = d;
    }else
    {
        parser_ = LMANAGER.add_constant_parser(d);
    }
}
        
LazyVariable::~LazyVariable()
{
    
}
        
double LazyVariable::get_value() const
{
    return creator_->get_value();
}
    
bool LazyVariable::is_null() const
{
    if (! parser_)  return true;
    return parser_->is_zero();
}

/////////////////////////////////////////////////////
//////////////////// operators ////// ///////////////
/////////////////////////////////////////////////////
 
LazyVariable LazyVariable::operator + (const LazyVariable& b) const
{
    LazyVariable out( LMANAGER.add_additionX(parser_,b.parser_));
    return out;    
}

LazyVariable LazyVariable::operator - (const LazyVariable& b) const
{
    return (*this + (b* -1));
}

LazyVariable LazyVariable::operator * (const LazyVariable& b) const
{
    LazyVariable out( LMANAGER.add_multiplicationX(parser_,b.parser_));
    return out;    
}

LazyVariable LazyVariable::operator * (double b) const
{
    LazyVariable out( LMANAGER.add_additionX(parser_,b));
    return out;
}

void LazyVariable::operator += (const LazyVariable& b)
{
    parser_ = LMANAGER.add_additionX(parser_,b.parser_);
}

void LazyVariable::operator -= (const LazyVariable& b)
{
    *this += (b*-1);
}

void LazyVariable::operator *= (const LazyVariable& b)
{
    parser_ = LMANAGER.add_multiplicationX(parser_,b.parser_);
}

std::ostream& operator<< (std::ostream& stream, const LazyVariable& v)
{
    stream << "@"<< v.parser_<<"@"<< v.creator_<<"@  TYPE : "<< v.parser_->typep_<<" eq : "<< v.parser_->get_name();
    return stream;
}
   
bool LazyVariable::operator != (const LazyVariable& b) const
{
    return ( parser_ != b.parser_ || creator_ != b.creator_);
}

LazyVariable cos (const LazyVariable& a)
{
    LazyVariable out (LMANAGER.add_cosinus(a.parser_));
    return out;
}

LazyVariable sin (const LazyVariable& a)
{
    LazyVariable out (LMANAGER.add_sinus(a.parser_));
    return out;
}

bool operator==(const LazyVariable& a, double d)
{
    return ! (a != LazyVariable(d));
}
