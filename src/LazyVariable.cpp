#include "LazyVariable.hpp"


LazyVariable::LazyVariable()
{
    parser_ = LMANAGER.add_constant_parser(0.0);
    creator_ = nullptr;
}

LazyVariable::LazyVariable(LazyParser* in)
{
//     std::cout<<" constructor"<<std::endl;
    parser_ = in ;
    creator_ = nullptr;
//     std::cout<<"\t constructor @("<<parser_<<") this "<< *(parser_)<<std::endl;
}

LazyVariable::LazyVariable(const LazyVariable& a)
{
//     std::cout<<"copy constructor"<<std::endl;
    parser_ = a.parser_;
    creator_ = a.creator_;
//     std::cout<<"\t copy constructor a    "<< *(a.parser_)<<std::endl;
//     std::cout<<"\t copy constructor this "<< *(parser_)<<std::endl;
}

void LazyVariable::operator = (const LazyVariable& a)
{
//     std::cout<<"copy operator ="<<std::endl;
    parser_ = a.parser_;
    creator_ = a.creator_;
//     std::cout<<"\t copy operator = a    "<< *(a.parser_)<<std::endl;
//     std::cout<<"\t copy operator = this "<< *(parser_)<<std::endl;    
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
    std::cout<<"Affectation operator = "<<d<<" de : "<<*this <<std::endl;
    
    if (parser_ == nullptr || LMANAGER.is_zero(parser_))
    {
        std::cout<<"on crée une constante" <<std::endl;
        parser_ = LMANAGER.add_constant_parser(d);
    }else
    if (parser_->typep_ == LAZYP_INPUT)
    {
        std::cout<<"on met à jour input = "<< d <<std::endl;
        ((LazyInput*) parser_)->value_ = d;
    }else
    {
        parser_ = LMANAGER.add_constant_parser(d);
//         if (parser_->typep_ == LAZYP_ADDITIONX)
//         {
//             LazyAdditionX* ax = (LazyAdditionX*) parser_;
//             if ( ! ax->is_double())
//             {
//                 std::cerr<<"Error in "<< __FILE__<<" at line "<<__LINE__<<std::endl;
//                 std::cerr<<"You cannot impose value"<<std::endl;
//                 exit(45);                
//             }else
//             {
//                 ax->p_[LMANAGER.get_one()] = d;
//             }
//         }else
//         {
//             std::cerr<<"Error in "<< __FILE__<<" at line "<<__LINE__<<std::endl;
//             std::cerr<<"You cannot impose value"<<std::endl;
//             exit(45);
//         }
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
//     std::cout<<"Operator+= avant this: "<< *this <<std::endl;
//     std::cout<<"Operator+= avant b: "<< b <<std::endl;
    parser_ = LMANAGER.add_additionX(parser_,b.parser_);
//     *this = *this + b;
//     std::cout<<"Operator+= après : "<< *this <<std::endl<<std::endl;
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
    stream << "@"<< v.parser_<<"@ "<<" TYPE : "<< v.parser_->typep_<<" eq : "<< v.parser_->get_name();
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
//     if (LMANAGER.is_constant(a.ref_) && a.ref_->value_ ==d)
//         return true;
//     return false;
}



