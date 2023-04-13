#ifndef __LAZYVALUE_HPP__
#define __LAZYVALUE_HPP__

#include <iostream>

class LazyValue
{
public:
    
    virtual ~LazyValue(){}
    
    virtual double evaluate(uint index=0) = 0;
    
    virtual void print( const std::string& tab ="", uint index=0) = 0;
    
    friend std::ostream& operator<< (std::ostream& stream, const LazyValue& v)
    {
        stream<<v.value_;
        return stream;
    }
    
    double value_;
    uint index_=0;
};

#endif // __LAZYVALUE_HPP__
