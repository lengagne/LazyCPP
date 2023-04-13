#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__


#include "LazyValue.hpp"

class LazyInput : public LazyValue {
public:
    LazyInput(double value, const std::string name="not_defined"); 
//     {        
//         value_ = value;
//         LMANAGER.add_input(this);
//     }
        
    double evaluate() { return value_; }

    virtual void print( const std::string& tab ="") 
    {
        std::cout<<tab<<"("<<this<<"): Input: "<<name_<<"("<<value_<<")"<<std::endl;
    }
    
    void operator = (const double & d)
    {
        value_ = d;
    }
        
private:
    std::string name_;
};

#endif // __LAZYINPUT_HPP__

