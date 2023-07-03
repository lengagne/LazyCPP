#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__


#include "LazyValue.hpp"

class LazyInput : public LazyValue {
public:
    LazyInput(double value, const std::string name="not_defined"); 
    
    virtual void add_to_list(std::vector<LazyValue*>& vec);
            
    virtual void check_known();
    
    virtual std::string file_print( const std::string& varname="x")
    {
        
    }

    virtual void print( const std::string& tab ="",uint index=0) ;
    
    virtual void print_equation();
    
    virtual void propag_update();
    
    virtual void re_init_known();
    
    void set_update(bool i);    
    
    void operator = (const double & d);

    std::string name_;
};

#endif // __LAZYINPUT_HPP__

