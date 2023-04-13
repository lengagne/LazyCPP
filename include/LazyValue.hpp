#ifndef __LAZYVALUE_HPP__
#define __LAZYVALUE_HPP__


class LazyValue
{
public:
    
    virtual ~LazyValue(){}
    
    virtual double evaluate() = 0;    
    
    friend std::ostream& operator<< (std::ostream& stream, const LazyValue& v)
    {
        stream<<v.value_;
        return stream;
    }
    
    double value_;
};

#endif // __LAZYVALUE_HPP__
