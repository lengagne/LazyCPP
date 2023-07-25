
#include "LazyConstant.hpp"

LazyConstant::LazyConstant(double value)
{
    type_ = LAZYCONSTANT;
    value_ = value;
    update_ = -1;
}    

LazyConstant::~LazyConstant()
{
}    
    


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
        
