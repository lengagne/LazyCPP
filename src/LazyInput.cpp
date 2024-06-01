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

LazyParser* LazyInput::do_simplification()
{
    return this;    
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

void LazyInput::update_list(std::vector<LazyCreator*>& vec, int current)
{
//     std::cout<<"no update I am an input"<<std::endl;
}

bool LazyInput::operator < ( const LazyInput& in) const
{
    return id_ < in.id_;
}
