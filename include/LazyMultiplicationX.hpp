#ifndef __LAZYMULTIPLICATIONX_HPP__
#define __LAZYMULTIPLICATIONX_HPP__

#include "LazyOperatorX.hpp"

class LazyMultiplicationX : public LazyOperatorX {
public:
    LazyMultiplicationX(std::vector<LazyValue*>& a);
    
    inline void compute();
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
