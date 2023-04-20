#ifndef __LAZYMULTIPLICATIONX_HPP__
#define __LAZYMULTIPLICATIONX_HPP__

#include "LazyOperatorX.hpp"

class LazyMultiplicationX : public LazyOperatorX {
public:
    LazyMultiplicationX(std::vector<LazyValue*>& a) 
    {
        p_ = a;
        compute();
    }
    
    inline void compute()
    {
        value_ = 1.0;
        for (int i=0;i<p_.size();i++)
            value_ *= p_[i]->value_;
    }    
    
    virtual void print( const std::string& tab ="",uint index=0) 
    {
        
        std::cout<<tab<<"("<<this<<"): MultiplicationX ("<<value_<<")"<<std::endl;
        for (int i=0;i<p_.size();i++)
            p_[i]->print(tab+"\t",index);

    }   
    
    virtual void print_equation()
    {
        std::cout<<"(";
        for (int i=0;i<p_.size();i++)
        {
            p_[i]->print_equation();
            if (i != p_.size()-1)   std::cout<<"*";   
        }
    }
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
