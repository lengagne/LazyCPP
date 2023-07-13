#include "LazyInput.hpp"


LazyInput::LazyInput(double value, const std::string name):name_(name) 
{            
    value_ = value;
    known_ = true;
}
    
void LazyInput::add_to_list(std::vector<LazyValue*>& vec)
{
    /// nothing to do
}
    
void LazyInput::check_known()
{
    /// nothing to do
}

void LazyInput::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyInput:("<<this<<"): Input: "<<name_<<"("<<value_<<")"<<std::endl;
}

void LazyInput::print_equation()
{
    std::cout<<name_;
}

void LazyInput::propag_update()
{
    /// nothing to do
}

void LazyInput::re_init_known()
{
    known_ = true;
}

void LazyInput::set_update(bool i)
{
    update_ = i;
}
