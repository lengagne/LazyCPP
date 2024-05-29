#ifndef __LAZYMULTIPLICATION_HPP__
#define __LAZYMULTIPLICATION_HPP__

#include "LazyOperator2.hpp"

class LazyMultiplication : public LazyOperator2 {
public:
    LazyMultiplication(LazyValue* a, LazyValue* b);
    
    inline void compute();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_string( )const ;
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
