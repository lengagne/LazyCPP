#ifndef __LAZYSINUS_HPP__
#define __LAZYSINUS_HPP__
#include <math.h>
#include "LazyParserCreator.hpp"

class LazySinus : public LazyParserCreator {
public:
    LazySinus(LazyParser* a);
    
    ~LazySinus()
    {
    }
    
    void compute();
    
    virtual LazyCreator* explose();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_name() const;

    virtual void print( const std::string& tab="") const; 
    
    virtual void print_tree( const std::string& tab ="");
    
    void update_list(std::vector<LazyCreator*>& vec, int current);
       
    
//     
//     virtual std::string get_string( )const ;
//     
    
//     
//     virtual void print_equation();    
    
private:
    LazyParser* pa_;
    LazyCreator* ca_;    

};

#endif //  __LAZYSINUS_HPP__
