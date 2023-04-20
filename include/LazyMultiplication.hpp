#ifndef __LAZYMULTIPLICATION_HPP__
#define __LAZYMULTIPLICATION_HPP__

#include "LazyOperator2.hpp"

class LazyMultiplication : public LazyOperator2 {
public:
    LazyMultiplication(LazyValue* a, LazyValue* b) {
        a_ = a;
        b_ = b;
        value_ = a->value_*b->value_;        
    }
    
    inline void compute()
    {
//         std::cout<<"Multiplication Compute a("<<a_->value_<<")*b("<<b_->value_<<")" <<std::endl;
        value_ = a_->value_ * b_->value_;
    }    
    
    virtual void print( const std::string& tab ="",uint index=0) 
    {
        std::cout<<tab<<"("<<this<<"): Multiplication ("<<value_<<")"<<std::endl;
        a_->print(tab+"\t",index);
        b_->print(tab+"\t",index);
    }   
    
    virtual void print_equation()
    {
        std::cout<<"(";
        a_->print_equation();
        std::cout<<"*";
        b_->print_equation();
        std::cout<<")";
    }
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
