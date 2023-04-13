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
    
    double evaluate() {
        value_ = a_->evaluate() * b_->evaluate();
        return value_;
    }

    virtual void print( const std::string& tab ="") 
    {
        std::cout<<tab<<"("<<this<<"): Multiplication: "<<std::endl;
        a_->print(tab+"\t");
        b_->print(tab+"\t");
    }    
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
