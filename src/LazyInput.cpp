#include "LazyInput.hpp"


LazyInput::LazyInput(double value, 
                     const std::string name):name_(name)
{          
    typec_ = LAZYC_INPUT;
    typep_ = LAZYP_INPUT;
    value_ = value;
}
    
void LazyInput::compute()
{
    
}


std::string LazyInput::file_print( const std::string& varname)
{
    return name_;
}

void LazyInput::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyInput:("<<this<<"): Input: "<<name_<<"("<<value_<<")"<<std::endl;
}
// 
// std::string LazyInput::get_string( )const 
// {
//     return name_; 
// }
// 
// 
// void LazyInput::print_equation()
// {
//     std::cout<<name_;
// }
// 
// void LazyInput::propag_update(int i)
// {
//     /// nothing to do
// }
// 
void LazyInput::update_list(std::vector<LazyCreator*>& vec, int current)
{
//     std::cout<<"no update I am an input"<<std::endl;
}
