#include "LazySoustraction.hpp"

LazySoustraction::LazySoustraction(LazyCreator* a, LazyCreator* b) 
{
    typec_ = LAZYC_SOUSTRACTION;
    a_ =a;
    b_ = b;
    compute();
}
    
void LazySoustraction::compute()
{
    value_ = a_->value_ - b_->value_;
}    

void LazySoustraction::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        a_->update_list(vec,current);
        b_->update_list(vec,current);
        vec.push_back(this);            
    }
    update_ = current;    
}

std::string LazySoustraction::file_print( const std::string& varname)
{
    return   varname+"["+ std::to_string(id_)+"] = " + a_->file_subname(varname) +" - "+ b_->file_subname(varname) +";";
}

std::string LazySoustraction::get_equation( )
{
    return a_->get_equation() + "-" + b_->get_equation();
}

void LazySoustraction::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazySoustraction(@"<<get_equation()<<")"<<std::endl;
    a_->print_tree(tab+"\t");
    b_->print_tree(tab+"\t");
}

bool LazySoustraction::operator < ( const LazySoustraction& in) const
{
    if (a_ < in.a_) return true;
    if (b_ < in.b_) return true;
    return false;
}
