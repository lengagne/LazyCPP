#ifndef __LAZYOPERATOR2_HPP__
#define __LAZYOPERATOR2_HPP__

#include "LazyValue.hpp"

class LazyOperator2 : public LazyValue {
public:
    
    virtual void add_to_list(std::vector<LazyValue*>& vec)
    {
        if (!known_)
        {
            a_->add_to_list(vec);
            b_->add_to_list(vec);
            vec.push_back(this);            
        }
        known_ =true;
    }    
   
//     virtual double evaluate(uint index)=0;
       
    virtual bool operator == (const LazyOperator2& A) const
    {
        return (a_ == A.a_ && b_ == A.b_) || (a_ == A.b_ && b_ == A.a_);
    }
    

    LazyValue* a_=nullptr;
    LazyValue* b_=nullptr;
};

#endif //  __LAZYADDITION_HPP__
