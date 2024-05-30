#ifndef __LAZYCOSINUS_HPP__
#define __LAZYCOSINUS_HPP__


#include <math.h>
#include "LazyParserCreator.hpp"

class LazyCosinus : public LazyParserCreator {
public:
    LazyCosinus(LazyParser* a);
    
    ~LazyCosinus()
    {
        
    }
    
    void compute();
    
    void set_creator_input( LazyCreator* in);
    
    virtual std::string get_name() const;
   
//     virtual 
    
    virtual std::string file_print( const std::string& varname="x");
    
    void update_list(std::vector<LazyCreator*>& vec, int current);
//     
//     virtual std::string get_string( )const ;
//     
    virtual void print( const std::string& tab="") const; 
//     
//     virtual void print_equation();
    
private:
    LazyParser* pa_;
    LazyCreator* ca_;

};

#endif //  __LAZYCOSINUS_HPP__
