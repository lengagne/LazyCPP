#ifndef __LAZYVALUE_HPP__
#define __LAZYVALUE_HPP__

#include <iostream>
#include <vector>

class LazyValue
{
public:
    
    virtual ~LazyValue(){}
    
    virtual void add_to_list(std::vector<LazyValue*>& vec) = 0;
    
    virtual inline void compute()
    {
        
    }
    
    void define_as_output();
    
    inline double get_value()const
    {
        return value_;
    }
    
    virtual double evaluate(uint index=0) = 0;
    
    virtual void print( const std::string& tab ="", uint index=0) = 0;
    
    virtual void re_init_known()
    {
        known_ = false;
    }
    
    friend std::ostream& operator<< (std::ostream& stream, const LazyValue& v)
    {
        stream<<v.value_;
        return stream;
    }
    
    double value_;
    uint index_=0;
    
    // defined if the value is already known;
    bool known_=false;
};

#endif // __LAZYVALUE_HPP__
