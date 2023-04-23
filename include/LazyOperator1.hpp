#ifndef __LAZYOPERATOR1_HPP__
#define __LAZYOPERATOR1_HPP__

#include "LazyValue.hpp"

class LazyOperator1 : public LazyValue {
public:
    
    /// update the list of the dependancies
    virtual void add_to_list(std::vector<LazyValue*>& vec);    
    
    virtual void check_known();
    
    virtual inline void compute() = 0;
           
    virtual bool operator == (const LazyOperator1& A) const;
    
    LazyValue* a_=nullptr;
};

#endif //  __LAZYADDITION_HPP__
