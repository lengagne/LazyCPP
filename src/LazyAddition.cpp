#include "LazyAddition.hpp"

LazyAddition::LazyAddition(LazyCreator* a, LazyCreator* b)
{
    typec_ = LAZYC_ADDITION;
    if (compareLazyCreator(a,b))
    {
        a_ = a;
        b_ = b; 
    }else
    {
        b_ = a;
        a_ = b;
    }
    compute();
}

void LazyAddition::compute()
{
    value_ = a_->value_ + b_->value_;
}

std::string LazyAddition::file_print( const std::string& varname)
{
    return   varname+"["+ std::to_string(id_)+"] = " + varname+"["+ std::to_string(a_->id_)+ "] + " + varname+"["+ std::to_string(b_->id_)+"];";
}

void LazyAddition::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        a_->update_list(vec,current);
        b_->update_list(vec,current);
        vec.push_back(this);            
    }
    update_ = current;    
}

/*
LazyAddition::LazyAddition(LazyValue* a, LazyValue* b)
{
    //std::cout<<"LazyAddition a,b"<<std::endl;
    type_ = LAZYADDITION;
    if (compareLazyValue(a,b))
    {
        a_ = a;
        b_ = b; 
    }else
    {
        b_ = a;
        a_ = b;
    }
    value_ = a->value_+b->value_;        
    //std::cout<<"Done LazyAddition a,b"<<std::endl;
}
    


*/
/*
std::string LazyAddition::get_string( ) const 
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
*/
