
#include "LazyConstant.hpp"

LazyConstant::LazyConstant(double value){
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
    
void LazyConstant::print( const std::string& tab ,uint index) 
{
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";

    std::cout<<tab<<"("<<this<<") Constante : "<< value_<<std::endl;
}    

void LazyConstant::print_equation()
{
    std::cout<< value_;
}    

void LazyConstant::re_init_known()
{
    // nothing to do
}


void LazyConstant::operator = (const double & d)
{
    value_ = d;
}
        
