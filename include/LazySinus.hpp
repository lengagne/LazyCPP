#ifndef __LAZYSINUS_HPP__
#define __LAZYSINUS_HPP__
#include <math.h>
#include "LazyOperator1.hpp"

class LazySinus : public LazyOperator1 {
public:
    LazySinus(LazyValue* a);
    
    inline void compute();
       
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_string( );
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();    
    
private:

};

#endif //  __LAZYSINUS_HPP__
