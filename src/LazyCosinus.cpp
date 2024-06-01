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

LazyParser* LazyCosinus::do_simplification()
{
    LazyParser* s = pa_->simplify();
    switch (s->typep_)
    {
        case(LAZYP_INPUT):
            return this;
        
        default:
            std::cerr<<"In file "<< __FILE__<<" at line "<< __LINE__ <<" the type "<< s->typep_ <<" is not implemented yet."<<std::endl;
            return this;
    }
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

void LazyCosinus::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyCosinus:("<<get_name()<<"): "<<std::endl;
    pa_->print(tab+"\t");
}

void LazyCosinus::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazyCosinus(@"<<this<<")"<<std::endl;
    ca_->print_tree(tab+"\t");
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

bool LazyCosinus::operator < ( const LazyCosinus& in) const
{
    return (pa_ < in.pa_);
}
