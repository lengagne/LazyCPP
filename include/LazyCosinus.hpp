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
    
    virtual LazyCreator* explose();
    
    virtual std::string get_name() const;
   
    virtual std::string file_print( const std::string& varname="x");
    
    virtual void print_tree( const std::string& tab ="");
    
    void update_list(std::vector<LazyCreator*>& vec, int current);

    virtual void print( const std::string& tab="") const;
    
    bool operator < ( const LazyCosinus& in) const;
    
private:
    LazyParser* pa_;
    LazyCreator* ca_;

};

#endif //  __LAZYCOSINUS_HPP__
