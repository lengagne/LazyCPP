#ifndef __LAZYOPERATOR1_HPP__
#define __LAZYOPERATOR1_HPP__

#include "LazyValue.hpp"

class LazyOperator1 : public LazyValue {
public:
    
    virtual void add_to_list(std::vector<LazyValue*>& vec)
    {
//         if (!known_)
        {
//             vec.insert(vec.begin(),this);
            a_->add_to_list(vec);
            vec.push_back(this);            
        }
        known_ =true;
    }    
   
//     virtual double evaluate(uint index)=0;
           
    virtual bool operator == (const LazyOperator1& A) const
    {
        return (a_ == A.a_ );
    }
    
    LazyValue* a_=nullptr;
};

#endif //  __LAZYADDITION_HPP__
