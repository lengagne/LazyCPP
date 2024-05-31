#include "LazyInput.hpp"


LazyInput::LazyInput(double value, 
                     const std::string name,int id):name_(name)
{          
    typec_ = LAZYC_INPUT;
    typep_ = LAZYP_INPUT;
    value_ = value;
    id_ = id;
}
    
LazyInput::~LazyInput()
{
    
}    
    
void LazyInput::compute()
{
    
}

LazyCreator* LazyInput::explose()
{
    return (LazyCreator*)this;
}

std::string LazyInput::get_name() const
{
    return name_;
}

std::string LazyInput::file_print( const std::string& varname)
{
    return name_;
}

void LazyInput::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyInput:("<<get_name()<<"): "<<name_<<"("<<value_<<")"<<std::endl;
}

void LazyInput::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazyInput(@"<<get_name()<<") : "<< name_<<std::endl;
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

bool LazyInput::operator < ( const LazyInput& in) const
{
//     std::cout<<"LazyInput::operator <  ("<< name_<<")"<< id_ <<" <? ("<<in.name_<<")"<< in.id_<<std::endl;
    return id_ < in.id_;
}
