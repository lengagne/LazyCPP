
#include "LazyCosinus.hpp"

LazyCosinus::LazyCosinus(LazyParser* a)
{
//     std::cout<<"LazyCosinus::LazyCosinus"<<std::endl;
    typec_ = LAZYC_COSINUS;
    typep_ = LAZYP_COSINUS;
    pa_ = a;
}
    
void LazyCosinus::compute()
{
    value_ = cos(ca_->value_);
}

LazyCreator* LazyCosinus::explose()
{
    ca_ = pa_->explose();
    return this;
}


std::string LazyCosinus::get_name() const
{
    return "cos(" + pa_->get_name() + ")";
}

std::string LazyCosinus::file_print( const std::string& varname)
{
//     return   varname+"["+ std::to_string(id_)+"] = cos(" + varname+"["+ std::to_string(ca_->id_)+ ")";    
    return   varname+"["+ std::to_string(id_)+"] = cos(" + ca_->file_subname(varname) +");";
}
// 
// std::string LazyCosinus::get_string( )const 
// {
//     return "cos(" + a_->get_string() + ")";
// }
//         
void LazyCosinus::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyCosinus:("<<get_name()<<"): "<<std::endl;
    pa_->print(tab+"\t");
}

void LazyCosinus::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazyCosinus(@"<<get_name()<<")"<<std::endl;
    ca_->print_tree(tab+"\t");
}

// 
// void LazyCosinus::print_equation()
// {
//     std::cout<<"cos(";
//     a_->print_equation();
//     std::cout<<")";      
// }


void LazyCosinus::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        ca_->update_list(vec,current);
        vec.push_back(this);            
    }
    update_ = current;    
}
