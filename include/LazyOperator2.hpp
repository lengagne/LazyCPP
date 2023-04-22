#ifndef __LAZYOPERATOR2_HPP__
#define __LAZYOPERATOR2_HPP__

#include "LazyValue.hpp"

class LazyOperator2 : public LazyValue {
public:
        
    virtual void check_known();
    
    virtual bool operator == (const LazyOperator2& A) const;

    LazyValue* a_=nullptr;
    LazyValue* b_=nullptr;
};

#endif //  __LAZYADDITION_HPP__
