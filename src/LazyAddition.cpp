
#include "LazyAddition.hpp"

LazyAddition::LazyAddition(LazyValue* a, LazyValue* b)
{
    type_ = LAZYADDITION;
//     if (a<b)
//     std::cout<<"LazyAddition"<<std::endl;
    if(compareLazyValue(a,b))
    {
        a_ = a;
        b_ = b; 
    }else
    {
        b_ = a;
        a_ = b;
    }
    value_ = a->value_+b->value_;        
}
    
inline void LazyAddition::compute()
{
    value_ = a_->value_ + b_->value_;
}



std::string LazyAddition::file_print( const std::string& varname)
{
    return   varname+"["+ std::to_string(id_)+"] = " + a_->file_subname(varname) + "+" + b_->file_subname(varname);
}

std::string LazyAddition::get_string( )
{
    return "(" + a_->get_string() + "+" + b_->get_string() + ")";
}
    
void LazyAddition::print( const std::string& tab ,uint index) 
{
    std::cout<<tab<<"LazyAddition:("<<this<<"): Addition ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
    b_->print(tab+"\t",index);
}
    
void LazyAddition::print_equation()
{
    std::cout<<"(";
    a_->print_equation();
    std::cout<<"+";
    b_->print_equation();
    std::cout<<")" ;
}

