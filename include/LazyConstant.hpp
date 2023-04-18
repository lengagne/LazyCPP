#ifndef __LAZYCONSTANT_HPP__
#define __LAZYCONSTANT_HPP__

#include "LazyValue.hpp"

class LazyConstant : public LazyValue {
public:
    LazyConstant(double value){
        value_ = value;
        known_ = true;
    }    
    
    void add_to_list(std::vector<LazyValue*>& vec)
    {
        /// nothing to do
    }
    
//     double evaluate(uint index) { return value_; }
    
    virtual void print( const std::string& tab ="",uint index=0) 
    {
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";

        std::cout<<tab<<"("<<this<<") Constante : "<< value_<<std::endl;
    }    
    
    
    virtual void re_init_known()
    {
        known_ = true;
    }
    
    
    void operator = (const double & d)
    {
        value_ = d;
    }
        
private:
};


#endif // __LAZYCONSTANT_HPP__

