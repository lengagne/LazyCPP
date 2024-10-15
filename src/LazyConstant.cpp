#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyConstant::LazyConstant(double value)
{
    typec_ = LAZYC_CONSTANT;
    typep_ = LAZYP_CONSTANT;
    value_ = value;
}    

LazyConstant::~LazyConstant()
{
    
}    

void LazyConstant::compute()
{
    
}

LazyParser* LazyConstant::do_simplification()
{
//     std::cout<<"LazyConstant::do_simplification() : "<< value_ <<std::endl;
    return this;
}

LazyCreator* LazyConstant::explose()
{
    return LMANAGER.add_constant(value_);
}
    
std::string LazyConstant::file_print( const std::string& varname)
{
    return to_string_with_precision(value_);
}

std::string LazyConstant::file_subname( const std::string& varname)
{
    return to_string_with_precision(value_);    
}

std::string LazyConstant::get_name() const
{
    return to_string_with_precision(value_);
}

bool LazyConstant::is_zero() const
{
    return (value_ == 0.0);
}

void LazyConstant::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyConstant:("<<get_name()<<"): "<< value_<<std::endl;    
}

void LazyConstant::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazyConstant(@"<<get_name()<<") : "<< value_<<std::endl;
}

void LazyConstant::update_list(std::vector<LazyCreator*>& vec, int current)
{
//     std::cout<<"On ajoute rien en LazyConstant"<<std::endl;
}

bool LazyConstant::operator < ( const LazyConstant& in) const
{
//     std::cout<<this<<" "<<value_<<" <? "<< &in <<" "<< in.value_<<"  return : "<< (value_ < in.value_) <<std::endl;
    return (value_ < in.value_);
}
