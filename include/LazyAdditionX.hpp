#ifndef __LAZYADDITIONX_HPP__
#define __LAZYADDITIONX_HPP__

#include "LazyOperatorX.hpp"
#include <map>

class LazyAdditionX : public LazyOperatorX {
public:
    LazyAdditionX(std::list<LazyValue*>& a);
    
    inline void compute();
    
    virtual void compact();
    
    virtual LazyValue* explose();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_string( )const ;
    
    virtual void print( const std::string& tab ="",uint index=0);
    
    virtual void print_equation();
    
    virtual void propag_update(int up =-1);
    
    virtual void remove_zeros();
    
    virtual void update_list(std::vector<LazyValue*>& vec, int current);
    
    virtual bool operator == (const LazyAdditionX& A) const;
    
    std::map<LazyValue*,double> p_;
    
private:

};

#endif // __LAZYMULTIPLICATION_HPP__
