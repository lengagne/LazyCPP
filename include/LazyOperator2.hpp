#ifndef __LAZYOPERATOR2_HPP__
#define __LAZYOPERATOR2_HPP__

#include "LazyValue.hpp"

class LazyOperator2 : public LazyValue {
public:
   
    virtual double evaluate(uint index)=0;
//     {
//         std::cout<<"index = "<< index <<std::endl;
//         std::cout<<"index_ = "<< index_ <<std::endl;
//         if (index > index_)
//         {
//             std::cout<<"update"<<std::endl;
//             index_ = index;
//             return evaluate();
//         }
//         return value_;
//     }
    
//     virtual double evaluate() = 0;
       
    virtual bool operator == (const LazyOperator2& A) const
    {
        return (a_ == A.a_ && b_ == A.b_) || (a_ == A.b_ && b_ == A.a_);
    }
    

    LazyValue* a_=nullptr;
    LazyValue* b_=nullptr;
};

#endif //  __LAZYADDITION_HPP__
