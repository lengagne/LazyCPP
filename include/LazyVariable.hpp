#ifndef __LAZYVARIABLE_HPP__
#define __LAZYVARIABLE_HPP__

// #include "LazyCPP.hpp"

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
           
    ~LazyVariable();
    
    double get_value() const;
    
    bool is_null() const;

    friend std::ostream& operator<< (std::ostream& stream, const LazyVariable& v);
    
    bool operator != (const LazyVariable& b) const;
  
    LazyVariable operator + (const LazyVariable& b) const;
    
    LazyVariable operator - (const LazyVariable& b) const;
    
    LazyVariable operator * (const LazyVariable& b) const;
    
private:
    LazyValue* ref_;
    
    friend class LazyManager;
    
    friend LazyVariable cos (const LazyVariable& a);

    friend LazyVariable sin (const LazyVariable& a);    
    
    LazyVariable(LazyValue* in);
};



#endif // __LAZYVARIABLE_HPP__
