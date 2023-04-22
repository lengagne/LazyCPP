#ifndef __LAZYOPPOSITE_HPP__
#define __LAZYOPPOSITE_HPP__
#include <math.h>
#include "LazyOperator1.hpp"

class LazyOpposite : public LazyOperator1 {
public:
    LazyOpposite(LazyValue* a);
    
    inline void compute();
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
    
private:

};

#endif //  __LAZYCOSINUS_HPP__
