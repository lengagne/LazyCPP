
#include "LazyCosinus.hpp"

LazyCosinus::LazyCosinus(LazyParser* a)
{
    typec_ = LAZYC_COSINUS;
    typep_ = LAZYP_COSINUS;
    pa_ = a;
    compute();
}
    
void LazyCosinus::compute()
{
    value_ = cos(ca_->value_);
}

void LazyCosinus::set_creator_input( LazyCreator* in)
{
    ca_ = in;
}

void LazyCosinus::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        ca_->update_list(vec,current);
        vec.push_back(this);            
    }
    update_ = current;    
}

std::string LazyCosinus::file_print( const std::string& varname)
{
    return   varname+"["+ std::to_string(id_)+"] = cos(" + varname+"["+ std::to_string(ca_->id_)+ ")";
}
// 
// std::string LazyCosinus::get_string( )const 
// {
//     return "cos(" + a_->get_string() + ")";
// }
//         
void LazyCosinus::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyCosinus:("<<this<<"): COSINUS "<<std::endl;
    pa_->print(tab+"\t");
}
// 
// void LazyCosinus::print_equation()
// {
//     std::cout<<"cos(";
//     a_->print_equation();
//     std::cout<<")";      
// }
