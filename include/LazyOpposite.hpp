#ifndef __LAZYOPPOSITE_HPP__
#define __LAZYOPPOSITE_HPP__
#include <math.h>
#include "LazyOperator1.hpp"

class LazyOpposite : public LazyOperator1 {
public:
    LazyOpposite(LazyValue* a){
        a_ = a;
        value_ = -(a_->value_);
    }
    
    inline void compute()
    {
//         std::cout<<"Cosinus Compute a("<<a_->value_ <<")"<<std::endl;
        value_ = -(a_->value_);
    }
    
    virtual void print( const std::string& tab ="",uint index=0) 
    {        
        std::cout<<tab<<"("<<this<<"): OPPOSITE ("<<value_<<")"<<std::endl;
        a_->print(tab+"\t",index);
    }
    
    virtual void print_equation()
    {
        std::cout<<"(-";
        a_->print_equation();
        std::cout<<")";
    }
    
    
private:

};

#endif //  __LAZYCOSINUS_HPP__
