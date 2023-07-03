#ifndef __LAZYCONSTANT_HPP__
#define __LAZYCONSTANT_HPP__

#include "LazyValue.hpp"

class LazyConstant : public LazyValue {
public:
    LazyConstant(double value);
    
    /// update the list of the dependancies
    virtual void add_to_list(std::vector<LazyValue*>& vec);
        
    virtual void check_known();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string file_subname( const std::string& varname="x")
    {
        return std::to_string(value_);
    }    
    
    virtual void print( const std::string& tab ="",uint index=0) ;

    virtual void print_equation();
    
    virtual void propag_update();
    
    virtual void re_init_known();
    
    void operator = (const double & d);
        
private:
};


#endif // __LAZYCONSTANT_HPP__

