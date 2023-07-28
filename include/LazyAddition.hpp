#ifndef __LAZYADDITION_HPP__
#define __LAZYADDITION_HPP__

#include "LazyOperator2.hpp"

class LazyAddition : public LazyOperator2 {
public:
    LazyAddition(LazyValue* a, LazyValue* b);
    
    inline void compute();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_string( );
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
private:

};

#endif //  __LAZYADDITION_HPP__
