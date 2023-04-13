#ifndef __LAZYSOUSTRACTION_HPP__
#define __LAZYSOUSTRACTION_HPP__

#include "LazyOperator2.hpp"

class LazySoustraction : public LazyOperator2 {
public:
    LazySoustraction(LazyValue* a, LazyValue* b) {
        a_ =a;
        b_ = b;
        value_ = a->value_-b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() - b_->evaluate();
        return value_;
    }
    
    virtual void print( const std::string& tab ="") 
    {
        std::cout<<tab<<"("<<this<<") Soustraction: "<<std::endl;
        a_->print(tab+"\t");
        b_->print(tab+"\t");
    }
    
private:
};


#endif // __LAZYSOUSTRACTION_HPP__
