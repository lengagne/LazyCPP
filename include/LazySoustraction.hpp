#ifndef __LAZYSOUSTRACTION_HPP__
#define __LAZYSOUSTRACTION_HPP__

#include "LazyOperator2.hpp"

class LazySoustraction : public LazyOperator2 {
public:
    LazySoustraction(LazyValue* a, LazyValue* b);
    
    inline void compute();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_string( )const ;
    
    virtual void print( const std::string& tab ="",uint index=0) ;
    
    virtual void print_equation();
    
    virtual bool operator == (const LazyOperator2& A) const;
    
private:
};


#endif // __LAZYSOUSTRACTION_HPP__
