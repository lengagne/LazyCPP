#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__

#include "LazyParserCreator.hpp"

class LazyInput : public LazyParserCreator {
public:
    LazyInput(double value, 
              const std::string name="not_defined"); 
        
    ~LazyInput()
    {
        
    }

    virtual void compute();
    
    virtual std::string file_print( const std::string& varname="x");

    virtual void print( const std::string& tab="") const; 

    virtual void update_list(std::vector<LazyCreator*>& vec, int current);

    std::string name_;
};

#endif // __LAZYINPUT_HPP__

