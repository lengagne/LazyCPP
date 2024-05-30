#include "LazyAddition.hpp"

LazyAddition::LazyAddition(LazyCreator* a, LazyCreator* b)
{
//     std::cout<<"LazyAddition::LazyAddition"<<std::endl;
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
    std::cout<<"LazyAddition::file_print : " <<std::endl;
    return   varname+"["+ std::to_string(id_)+"] = " + a_->file_subname(varname) +" + "+ b_->file_subname(varname) +";";
}

std::string LazyAddition::get_equation( )
{
    return a_->get_equation() + "+" + b_->get_equation();
}

void LazyAddition::print_tree( const std::string& tab)
{
    std::cout<<tab<<"LazyAddition(@"<<this<<")"<<std::endl;
    a_->print_tree(tab+"\t");
    b_->print_tree(tab+"\t");
}

void LazyAddition::update_list(std::vector<LazyCreator*>& vec, int current)
{
    if (update_ < current)
    {
        a_->update_list(vec,current);
        b_->update_list(vec,current);
        std::cout<<"On ajoute LazyAddition"<<std::endl;
        vec.push_back(this);            
    }
    update_ = current;    
}

bool LazyAddition::operator < ( const LazyAddition& in) const
{
    if (a_ < in.a_) return true;
    if (b_ < in.b_) return true;
    return false;
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
