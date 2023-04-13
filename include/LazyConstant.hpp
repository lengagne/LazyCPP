#ifndef __LAZYCONSTANT_HPP__
#define __LAZYCONSTANT_HPP__

#include "LazyValue.hpp"

class LazyConstant : public LazyValue {
public:
    LazyConstant(double value){value_ = value;}
    double evaluate() { return value_; }
    void operator = (const double & d)
    {
        value_ = d;
    }
        
private:
};


#endif // __LAZYCONSTANT_HPP__

