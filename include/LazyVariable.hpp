#ifndef __LAZYVARIABLE_HPP__
#define __LAZYVARIABLE_HPP__

#include "LazyManager.hpp"

class LazyVariable
{
public:
    LazyVariable();
    
    LazyVariable(LazyParser* in);
    
    LazyVariable(const LazyVariable& a);
    
    LazyVariable(const uint & a);

    LazyVariable(const int & a);
    
    LazyVariable(const double & a);
    
    LazyVariable(const double &a, const std::string& name);
    
    LazyVariable(const std::string& name);
   
    // modif value
    void operator = (double d);
    
    void operator = (const LazyVariable& a);
           
    ~LazyVariable();
    
    double get_value() const;
    
    bool is_null() const;

    friend std::ostream& operator<< (std::ostream& stream, const LazyVariable& v);
    
    bool operator != (const LazyVariable& b) const;
    
    friend bool operator==(const LazyVariable& a, double d);
  
    LazyVariable operator + (const LazyVariable& b) const;
    
    LazyVariable operator - (const LazyVariable& b) const;
    
    LazyVariable operator * (const LazyVariable& b) const;
    
    LazyVariable operator * (double b) const;
    
    void operator += (const LazyVariable& b);
    
    void operator -= (const LazyVariable& b);
    
    void operator *= (const LazyVariable& b);

    void print_equation()
    {
        parser_->print();
    }
    
// private:
    LazyParser* parser_;
    LazyCreator* creator_;
    
    friend LazyVariable cos (const LazyVariable& a);

    friend LazyVariable sin (const LazyVariable& a);    
    
    friend void LazyAddOutput(LazyVariable& in,uint index,uint rank);
        
};

inline LazyVariable operator + (double a, const LazyVariable& b)
{
    return b+a;
}

inline LazyVariable operator - (double a, const LazyVariable& b)
{
    return ((LazyVariable) a)-b;
}


inline LazyVariable operator * (double a, const LazyVariable& b)
{
    return b*a;
}

inline LazyVariable operator / (const LazyVariable& a, double b)
{
    return a*(1.0/b);
}

#endif // __LAZYVARIABLE_HPP__
