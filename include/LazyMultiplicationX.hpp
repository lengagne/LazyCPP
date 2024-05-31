#ifndef __LAZYMULTIPLICATIONX_HPP__
#define __LAZYMULTIPLICATIONX_HPP__

#include <list>
#include "LazyParser.hpp"

class LazyMultiplicationX : public LazyParser {
public:
    LazyMultiplicationX(std::list<LazyParser*>& a);
    
    double get_constant() const;
    
    LazyParser* get_without_constant() const;
    
//     inline void compute();
//     
    virtual double compact(std::list<LazyParser*> in);
//     
    virtual LazyCreator* explose();
    
    virtual std::string get_name() const;
    
    virtual bool is_zero() const;
//     
//     virtual std::string file_print( const std::string& varname="x");
//     
//     virtual std::string get_string( )const ;
//     
    virtual void print( const std::string& tab ="") const;
    
    virtual LazyParser* simplify();
//     
//     virtual void print_equation();
//     
//     virtual void propag_update(int up =-1);
//     
//     virtual void update_list(std::vector<LazyValue*>& vec, int current);
//     
//     virtual bool operator == (const LazyMultiplicationX& A) const;
    
    std::list<LazyParser*> p_;
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
