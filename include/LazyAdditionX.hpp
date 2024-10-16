#ifndef __LAZYADDITIONX_HPP__
#define __LAZYADDITIONX_HPP__

#include <list>
#include <map>

#include "LazyParser.hpp"

class LazyAdditionX : public LazyParser {
public:
    LazyAdditionX() ;
    
    LazyAdditionX(std::list<LazyParser*>& a);
    
    LazyAdditionX(double in ) ;
    
    LazyAdditionX(double coeff, LazyParser* in);
    
    virtual LazyParser* do_simplification();
    
    virtual LazyCreator* explose();
    
    double get_double();
    
    virtual std::string get_name() const;
    
    bool is_double() const;
    
    virtual bool is_zero() const;
    
    virtual void print( const std::string& tab="") const; 
    
    bool operator < ( const LazyAdditionX& in) const;
    
    std::map<LazyParser*,double> p_;
    
private:
    
    void remove_zeros();

};

#endif // __LAZYMULTIPLICATION_HPP__
