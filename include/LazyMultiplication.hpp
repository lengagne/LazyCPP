#ifndef __LAZYMULTIPLICATION_HPP__
#define __LAZYMULTIPLICATION_HPP__

class LazyMultiplication : public LazyValue {
public:
    LazyMultiplication(LazyValue* a, LazyValue* b) : a_(a), b_(b) {
        value_ = a->value_*b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() * b_->evaluate();
        return value_;
    }
    
private:
    LazyValue* a_;
    LazyValue* b_;
};

#endif // __LAZYMULTIPLICATION_HPP__
