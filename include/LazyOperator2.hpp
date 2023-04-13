#ifndef __LAZYOPERATOR2_HPP__
#define __LAZYOPERATOR2_HPP__

#include "LazyValue.hpp"

class LazyOperator2 : public LazyValue {
public:
   
    virtual double evaluate() = 0;
       
    virtual bool operator == (const LazyOperator2& A) const
    {
        std::cout<<"a_ = "<< a_<< std::endl;
        std::cout<<"A.a_ = "<< A.a_<< std::endl;
        std::cout<<"first = "<< (a_ == A.a_) << std::endl;
        std::cout<<"b_ = "<< b_<< std::endl;
        std::cout<<"A.b_ = "<< A.b_<< std::endl;
        std::cout<<"second = "<< (b_ == A.b_)<< std::endl;        
        return a_ == A.a_ && b_ == A.b_;
    }
    
protected:
    LazyValue* a_=nullptr;
    LazyValue* b_=nullptr;
};

#endif //  __LAZYADDITION_HPP__
