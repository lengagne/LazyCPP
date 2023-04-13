#ifndef __LAZYADDITION_HPP__
#define __LAZYADDITION_HPP__

#include "LazyOperator2.hpp"

class LazyAddition : public LazyOperator2 {
public:
    LazyAddition(LazyValue* a, LazyValue* b){
        a_ = a;
        b_ = b;
        value_ = a->value_+b->value_;        
    }
    
    double evaluate(uint index) 
    {
        if (index > index_)
        {
            index_ = index;
            value_ = a_->evaluate(index_) + b_->evaluate(index_);
            return value_;
        }
//         std::cout<<"Add Use previous computation"<<std::endl;
        return value_;
    }
    
    virtual void print( const std::string& tab ="",uint index=0) 
    {
        if (index > index_)
            std::cout<<"\x1B[35m";
        else
            std::cout<<"\x1B[32m";
        
        std::cout<<tab<<"("<<this<<"): Addition ("<<value_<<")"<<std::endl;
        a_->print(tab+"\t",index);
        b_->print(tab+"\t",index);
    }
    
    
private:

};

#endif //  __LAZYADDITION_HPP__
