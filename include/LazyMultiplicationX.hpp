#ifndef __LAZYMULTIPLICATIONX_HPP__
#define __LAZYMULTIPLICATIONX_HPP__

#include "LazyOperatorX.hpp"

class LazyMultiplicationX : public LazyOperatorX {
public:
    LazyMultiplicationX(std::list<LazyValue*>& a);
    
    inline void compute();
    
    virtual void compact();
    
    virtual LazyValue* explose();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_string( );
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
