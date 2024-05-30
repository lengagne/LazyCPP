
#include "LazySinus.hpp"

LazySinus::LazySinus(LazyParser* a)
{
    typec_ = LAZYC_SINUS;
    typep_ = LAZYP_SINUS;
    pa_ = a;
}
    
void LazySinus::compute()
{
    value_ = sin(ca_->value_);
}

LazyCreator* LazySinus::explose()
{
    ca_ = pa_->explose();
    return this;
}

std::string LazySinus::get_name() const
{
    return "sin(" + pa_->get_name() + ")";
}
    
std::string LazySinus::file_print( const std::string& varname)
{
//     return   varname+"["+ std::to_string(id_)+"] = sin(" + varname+"["+ std::to_string(ca_->id_)+ ")";
    return   varname+"["+ std::to_string(id_)+"] = sin(" +ca_->file_subname(varname) + ");";
}

// 
// std::string LazySinus::get_string( )const 
// {
//     return "sin(" + a_->get_string() + ")";
// }
// 
void LazySinus::print( const std::string& tab) const
{
    std::cout<<tab<<"LazySinus:("<<this<<"): "<<std::endl;
    pa_->print(tab+"\t");
}

void LazySinus::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazySinus(@"<<this<<")"<<std::endl;
    ca_->print_tree(tab+"\t");
}
// 
// void LazySinus::print_equation()
// {
//     std::cout<<"sin(";
//     a_->print_equation();
//     std::cout<<")";
// }
//     

void LazySinus::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        ca_->update_list(vec,current);
        vec.push_back(this);            
    }
    update_ = current;    
}
