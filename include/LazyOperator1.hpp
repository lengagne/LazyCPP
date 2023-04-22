#ifndef __LAZYOPERATOR1_HPP__
#define __LAZYOPERATOR1_HPP__

#include "LazyValue.hpp"

class LazyOperator1 : public LazyValue {
public:
    
    virtual void check_known();
           
    virtual bool operator == (const LazyOperator1& A) const;
    
    LazyValue* a_=nullptr;
};

#endif //  __LAZYADDITION_HPP__
