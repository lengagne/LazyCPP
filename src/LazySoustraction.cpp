
#include "LazySoustraction.hpp"

LazySoustraction::LazySoustraction(LazyValue* a, LazyValue* b) 
{
    a_ =a;
    b_ = b;
    value_ = a->value_-b->value_;        
}
    
inline void LazySoustraction::compute()
{
    value_ = a_->value_ - b_->value_;
}    
    
void LazySoustraction::print( const std::string& tab ,uint index) 
{
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";
    
    std::cout<<tab<<"("<<this<<") Soustraction ("<<value_<<")"<<std::endl;
    a_->print(tab+"\t",index);
    b_->print(tab+"\t",index);
}
    
void LazySoustraction::print_equation()
{
    std::cout<<"(";
    a_->print_equation();
    std::cout<<" - ";
    b_->print_equation();
    std::cout<<")";
}
    
bool LazySoustraction::operator == (const LazyOperator2& A) const
{
    return (a_ == A.a_ && b_ == A.b_);
}    
    
