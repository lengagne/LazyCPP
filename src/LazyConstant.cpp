
#include "LazyConstant.hpp"

LazyConstant::LazyConstant(double value)
{
    type_ = LAZYCONSTANT;
    value_ = value;
    known_ = true;
}    
    
void LazyConstant::add_to_list(std::vector<LazyValue*>& vec)
{
    /// nothing to do
}
    
void LazyConstant::check_known()
{
    /// nothing to do
}    

std::string LazyConstant::file_subname( const std::string& varname)
{
    return to_string_with_precision(value_,30);
}    


std::string LazyConstant::file_print( const std::string& varname)
{
    return file_subname(varname);
}
    
void LazyConstant::print( const std::string& tab ,uint index) 
{
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";

    std::cout<<tab<<"LazyConstant:("<<this<<") Constante : "<< value_<<std::endl;
}    

void LazyConstant::print_equation()
{
    std::cout<< value_;
}    

void LazyConstant::propag_update()
{
    update_ = false;
}

void LazyConstant::re_init_known()
{
    // nothing to do
}


void LazyConstant::operator = (const double & d)
{
    value_ = d;
}
        
