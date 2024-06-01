#ifndef __LAZYMULTIPLICATIONX_HPP__
#define __LAZYMULTIPLICATIONX_HPP__

#include <list>
#include "LazyParser.hpp"

class LazyMultiplicationX : public LazyParser {
public:
    LazyMultiplicationX(std::list<LazyParser*>& a);
    
//     double get_constant() const;
    
//     LazyParser* get_without_constant();

    virtual LazyCreator* explose();
    
    virtual std::string get_name() const;
    
    virtual bool is_zero() const;

    virtual void print( const std::string& tab ="") const;
    
    virtual LazyParser* simplify();
    
    bool operator < ( const LazyMultiplicationX& in) const;
    
    std::list<LazyParser*> p_;
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
