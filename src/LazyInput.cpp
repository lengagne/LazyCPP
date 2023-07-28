#include "LazyInput.hpp"


LazyInput::LazyInput(double value, const std::string name):name_(name) 
{            
    value_ = value;
    update_ = -1;
}
    

void LazyInput::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyInput:("<<this<<"): Input: "<<name_<<"("<<value_<<")"<<std::endl;
}

std::string LazyInput::get_string( )
{
    return name_; 
}


void LazyInput::print_equation()
{
    std::cout<<name_;
}

void LazyInput::propag_update(int i)
{
    /// nothing to do
}

void LazyInput::update_list(std::vector<LazyValue*>& vec, int current)
{
//     std::cout<<"no update I am an input"<<std::endl;
}
