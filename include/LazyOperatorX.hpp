#ifndef __LAZYOPERATORX_HPP__
#define __LAZYOPERATORX_HPP__

#include "LazyValue.hpp"
#include <list>

class LazyOperatorX : public LazyValue {
public:
    
    /// update the list of the dependancies
//     virtual void add_to_list(std::vector<LazyValue*>& vec);    
    
//     virtual void check_known();
    
    virtual inline void compute() = 0;
    
    virtual void compact() = 0;
    
    virtual LazyValue* explose() = 0;
    
    virtual void propag_update(int up =-1);
    
    virtual void update_list(std::vector<LazyValue*>& vec, int current);
       
    virtual bool operator == (const LazyOperatorX& A) const;

    std::list<LazyValue*> p_;
    
    LazyValue* exploded_ptr_ = nullptr;
};


#endif //  __LAZYADDITION_HPP__
