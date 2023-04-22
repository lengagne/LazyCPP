#ifndef __LAZYOPERATORX_HPP__
#define __LAZYOPERATORX_HPP__

#include "LazyValue.hpp"
#include <list>

class LazyOperatorX : public LazyValue {
public:
    
    /// update the list of the dependancies
    virtual void add_to_list(std::vector<LazyValue*>& vec);    
    
    virtual void check_known();
       
    virtual bool operator == (const LazyOperatorX& A) const;

    double constant_;
    std::list<LazyValue*> p_;
};

#endif //  __LAZYADDITION_HPP__
