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

LazyParser* LazySinus::do_simplification()
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
    return   varname+"["+ std::to_string(id_)+"] = sin(" +ca_->file_subname(varname) + ");";
}

void LazySinus::print( const std::string& tab) const
{
    std::cout<<tab<<"LazySinus:("<<get_name()<<"): "<<std::endl;
    pa_->print(tab+"\t");
}

void LazySinus::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazySinus(@"<<this<<")"<<std::endl;
    ca_->print_tree(tab+"\t");
}

void LazySinus::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        ca_->update_list(vec,current);
        vec.push_back(this);            
    }
    update_ = current;    
}

bool LazySinus::operator < ( const LazySinus& in) const
{
    return (pa_ < in.pa_);
}
