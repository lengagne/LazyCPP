
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
//     return   varname+"["+ std::to_string(id_)+"] = " + varname+"["+ std::to_string(a_->id_)+ "] - " + varname+"["+ std::to_string(b_->id_)+"];";
    return   varname+"["+ std::to_string(id_)+"] = " + a_->file_subname(varname) +" - "+ b_->file_subname(varname) +";";
}

std::string LazySoustraction::get_equation( )
{
    return a_->get_equation() + "-" + b_->get_equation();
}

void LazySoustraction::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazySoustraction(@"<<this<<")"<<std::endl;
    a_->print_tree(tab+"\t");
    b_->print_tree(tab+"\t");
}


//     
// void LazySoustraction::print( const std::string& tab ,uint index) 
// {
//     std::cout<<tab<<"LazySoustraction:("<<this<<") Soustraction ("<<value_<<")"<<std::endl;
//     a_->print(tab+"\t",index);
//     b_->print(tab+"\t",index);
// }
//     
// std::string LazySoustraction::get_string( )const 
// {
//     return "(" + a_->get_string() + "-" + b_->get_string() + ")";
// }    
//     
// void LazySoustraction::print_equation()
// {
//     std::cout<<"(";
//     a_->print_equation();
//     std::cout<<" - ";
//     b_->print_equation();
//     std::cout<<")";
// }
//     
// bool LazySoustraction::operator == (const LazyOperator2& A) const
// {
//     return (a_ == A.a_ && b_ == A.b_);
// }    
//     
