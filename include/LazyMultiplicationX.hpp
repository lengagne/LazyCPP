#ifndef __LAZYMULTIPLICATIONX_HPP__
#define __LAZYMULTIPLICATIONX_HPP__

#include "LazyOperatorX.hpp"

class LazyMultiplicationX : public LazyOperatorX {
public:
    LazyMultiplicationX(std::list<LazyValue*>& a);
    
    inline void compute();
    
    virtual void compact();
    
    virtual LazyValue* explose();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_string( )const ;
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
    virtual void propag_update(int up =-1);
    
    virtual void update_list(std::vector<LazyValue*>& vec, int current);
    
    virtual bool operator == (const LazyMultiplicationX& A) const;
    
    std::list<LazyValue*> p_;
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
