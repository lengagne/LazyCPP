#include "LazyVariable.hpp"


LazyVariable::LazyVariable()
{
    parser_ = nullptr;
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
    
LazyVariable::LazyVariable(const double &a, const std::string& name)
{
    parser_ = LMANAGER.add_input(a,name);
    creator_ = nullptr;
}
    
LazyVariable::LazyVariable(const std::string& name) 
{
    parser_ = LMANAGER.add_input(0,name);
    creator_ = nullptr;
}

void LazyVariable::operator = (double d)
{
    if (parser_->typep_ == LAZYP_INPUT)
    {
        ((LazyInput*) parser_)->value_ = d;
    }else
    {
        if (parser_->typep_ == LAZYP_ADDITIONX)
        {
            LazyAdditionX* ax = (LazyAdditionX*) parser_;
            if ( ! ax->is_double())
            {
                std::cerr<<"Error in "<< __FILE__<<" at line "<<__LINE__<<std::endl;
                std::cerr<<"You cannot impose value"<<std::endl;
                exit(45);                
            }else
            {
                ax->p_[nullptr] = d;
            }
        }else
        {
            std::cerr<<"Error in "<< __FILE__<<" at line "<<__LINE__<<std::endl;
            std::cerr<<"You cannot impose value"<<std::endl;
            exit(45);
        }
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
//     LazyVariable out( LMANAGER.add_soustraction(ref_, b.ref_));
//     return out;    
    
    return *this + (-1*b);
}

LazyVariable LazyVariable::operator * (const LazyVariable& b) const
{
    LazyVariable out( LMANAGER.add_multiplicationX(parser_,b.parser_));
    return out;    
}

void LazyVariable::operator += (const LazyVariable& b)
{
    parser_ = LMANAGER.add_additionX(parser_,b.parser_);
}

void LazyVariable::operator -= (const LazyVariable& b)
{
//     parser_ = LMANAGER.add_soustraction(parser_,b.parser_);
    *this += (-1*b);
}

void LazyVariable::operator *= (const LazyVariable& b)
{
    parser_ = LMANAGER.add_multiplicationX(parser_,b.parser_);
}

std::ostream& operator<< (std::ostream& stream, const LazyVariable& v)
{
//     v.ref_->print_equation();
//     stream << v.ref_->value_;
//     stream <<  v.parser_->get_string();
    stream<<"Not coded yet ";
    return stream;
}
   
    
// bool LazyVariable::operator != (const LazyVariable& b) const
// {
//     return ref_ != b.ref_;
// }

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

// bool operator==(const LazyVariable& a, double d)
// {
//     if (LMANAGER.is_constant(a.ref_) && a.ref_->value_ ==d)
//         return true;
//     return false;
// }



