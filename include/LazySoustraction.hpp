#ifndef __LAZYSOUSTRACTION_HPP__
#define __LAZYSOUSTRACTION_HPP__

#include "LazyValue.hpp"

class LazySoustraction : public LazyValue {
public:
    LazySoustraction(LazyValue* a, LazyValue* b) : a_(a), b_(b) {
        value_ = a->value_-b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() - b_->evaluate();
        return value_;
    }
    
private:
    LazyValue* a_;
    LazyValue* b_;
};


#endif // __LAZYSOUSTRACTION_HPP__
