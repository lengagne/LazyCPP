#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__


#include "LazyValue.hpp"

class LazyInput : public LazyValue {
public:
    LazyInput(double value); 
//     {        
//         value_ = value;
//         LMANAGER.add_input(this);
//     }
        
    double evaluate() { return value_; }
    void operator = (const double & d)
    {
        value_ = d;
    }
        
private:
};

#endif // __LAZYINPUT_HPP__

