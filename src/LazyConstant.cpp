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

LazyCreator* LazyConstant::explose()
{
    return LMANAGER.add_constant(value_);
}
    
std::string LazyConstant::file_print( const std::string& varname)
{
    return std::to_string(value_);
}

std::string LazyConstant::get_name() const
{
    return std::to_string(value_);
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
//     std::cout<<value_<<" <? "<< in.value_<<std::endl;
    return (value_ < in.value_);
}
/*

std::string LazyConstant::file_subname( const std::string& varname)
{
    return to_string_with_precision(value_,20);
//     return std::to_string(value_);
}    


std::string LazyConstant::file_print( const std::string& varname)
{
    return file_subname(varname);
}
    
void LazyConstant::print( const std::string& tab ,uint index) 
{
    std::cout<<tab<<"LazyConstant:("<<this<<") Constante : "<< value_<<std::endl;
}    

std::string LazyConstant::get_string( )const 
{
    return std::to_string(value_); 
}

void LazyConstant::print_equation()
{
    std::cout<< value_;
}    

void LazyConstant::propag_update(int v)
{
    update_ = -1;
}

void LazyConstant::update_list(std::vector<LazyValue*>& vec, int current)
{
//     std::cout<<"no update I am a constant"<<std::endl;
}

void LazyConstant::operator = (const double & d)
{
    value_ = d;
}
        */
