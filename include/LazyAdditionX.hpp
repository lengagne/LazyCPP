#ifndef __LAZYADDITIONX_HPP__
#define __LAZYADDITIONX_HPP__

#include "LazyOperatorX.hpp"

class LazyAdditionX : public LazyOperatorX {
public:
    LazyAdditionX(std::list<LazyValue*>& a);
    
    inline void compute();
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
