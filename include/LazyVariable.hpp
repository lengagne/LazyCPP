#ifndef __LAZYVARIABLE_HPP__
#define __LAZYVARIABLE_HPP__

#include "LazyManager.hpp"


class LazyVariable
{
public:
    LazyVariable();
    
    LazyVariable(const LazyVariable& a);
    
    LazyVariable(const uint & a);

    LazyVariable(const int & a);
    
    LazyVariable(const double & a);
    
    LazyVariable(const double &a, const std::string& name);
    
    LazyVariable(const std::string& name);
    
    // modif value
    void operator = (double d);
           
    ~LazyVariable();
    
    double get_value() const;
    
    bool is_null() const;

    friend std::ostream& operator<< (std::ostream& stream, const LazyVariable& v);
    
    bool operator != (const LazyVariable& b) const;
  
    LazyVariable operator + (const LazyVariable& b) const;
    
    LazyVariable operator - (const LazyVariable& b) const;
    
    LazyVariable operator * (const LazyVariable& b) const;
    
    void operator += (const LazyVariable& b);
    
    void operator -= (const LazyVariable& b);
    
    void operator *= (const LazyVariable& b);
    
private:
    LazyValue* ref_;
    
    friend class LazyManager;
    
    friend LazyVariable cos (const LazyVariable& a);

    friend LazyVariable sin (const LazyVariable& a);    
    
    friend void LazyAddOutput(LazyVariable& in,uint index,uint rank);
    
    LazyVariable(LazyValue* in);
};

inline LazyVariable operator * (double a, const LazyVariable& b)
{
    return b*a;
}

inline LazyVariable operator / (const LazyVariable& a, double b)
{
    return a*(1.0/b);
}

#endif // __LAZYVARIABLE_HPP__
