#include "LazyMultiplication.hpp"

LazyMultiplication::LazyMultiplication(LazyCreator* a, LazyCreator* b) 
{
    typec_ = LAZYC_MULTIPLICATION;
    if (compareLazyCreator(a,b))
    {
        a_ = a;
        b_ = b; 
    }else
    {
        b_ = a;
        a_ = b;
    }
    value_ = a->value_*b->value_;        
}
    
inline void LazyMultiplication::compute()
{
    value_ = a_->value_ * b_->value_;
}    

std::string LazyMultiplication::file_print( const std::string& varname)
{
    return   varname+"["+ std::to_string(id_)+"] = " + a_->file_subname(varname) + " * " + b_->file_subname(varname) +";";
}

std::string LazyMultiplication::get_equation( )
{
    return a_->get_equation() + "*" + b_->get_equation();
}

void LazyMultiplication::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazyMultiplication(@"<<this<<")"<<std::endl;
    a_->print_tree(tab+"\t");
    b_->print_tree(tab+"\t");
}

void LazyMultiplication::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        std::cout<<"On ajoute LazyMulitplication"<<std::endl;
        a_->update_list(vec,current);
        b_->update_list(vec,current);
        vec.push_back(this);            
    }
    update_ = current;    
}

bool LazyMultiplication::operator < ( const LazyMultiplication& in) const
{
    if (a_ < in.a_) return true;
    if (b_ < in.b_) return true;
    return false;
}


// std::string LazyMultiplication::get_string( )const 
// {
//     return "(" + a_->get_string() + "*" + b_->get_string() + ")";
// }
//     
// void LazyMultiplication::print( const std::string& tab,uint index) 
// {
//     std::cout<<tab<<"LazyMultiplication:("<<this<<"): Multiplication ("<<value_<<")"<<std::endl;
//     a_->print(tab+"\t",index);
//     b_->print(tab+"\t",index);
// }   
//     
// void LazyMultiplication::print_equation()
// {
//     std::cout<<"(";
//     a_->print_equation();
//     std::cout<<"*";
//     b_->print_equation();
//     std::cout<<")";
// }
    
