#ifndef __LAZYADDITION_HPP__
#define __LAZYADDITION_HPP__

#include "LazyOperator2.hpp"

class LazyAddition : public LazyOperator2 {
public:
    LazyAddition(LazyValue* a, LazyValue* b){
        a_ = a;
        b_ = b;
        value_ = a->value_+b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() + b_->evaluate();
        return value_;
    }
    
    virtual void print( const std::string& tab ="") 
    {
        std::cout<<tab<<"("<<this<<"): Addition "<<std::endl;
        a_->print(tab+"\t");
        b_->print(tab+"\t");
    }
    
    
private:

};

#endif //  __LAZYADDITION_HPP__
