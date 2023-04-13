#ifndef __LAZYADDITION_HPP__
#define __LAZYADDITION_HPP__

#include "LazyValue.hpp"

class LazyAddition : public LazyValue {
public:
    LazyAddition(LazyValue* a, LazyValue* b) : a_(a), b_(b) {
        value_ = a->value_+b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() + b_->evaluate();
        return value_;
    }
    
private:
    LazyValue* a_;
    LazyValue* b_;
};

#endif //  __LAZYADDITION_HPP__
