#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__


#include "LazyValue.hpp"

class LazyInput : public LazyValue {
public:
    LazyInput(double value, const std::string name="not_defined"); 
    
    void add_to_list(std::vector<LazyValue*>& vec)
    {
        /// nothing to do
    }    
        
    double evaluate(uint index) { return value_; }

    virtual void print( const std::string& tab ="",uint index=0) 
    {
        if (index > index_)
            std::cout<<"\x1B[35m";
        else
            std::cout<<"\x1B[32m";
        
        std::cout<<tab<<"("<<this<<"): Input: "<<name_<<"("<<value_<<")"<<std::endl;
    }
    
    virtual void re_init_known()
    {
        known_ = true;
    }
    
    void operator = (const double & d);
//     {
//         value_ = d;
//     }
    
//     void set_value( const double & d)
//     {
//         value_ = d;
//     }
        
private:
    std::string name_;
};

#endif // __LAZYINPUT_HPP__

