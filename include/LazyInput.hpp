#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__


#include "LazyValue.hpp"

class LazyInput : public LazyValue {
public:
    LazyInput(double value, 
              const std::string name="not_defined",
              int id = -1); 
        
    void compact()
    {
        
    }    
    
    virtual LazyValue* explose()
    {
        return this;
    }
    
    virtual std::string file_print( const std::string& varname="x")
    {
        
    }
    
    virtual std::string get_string( );

    virtual void print( const std::string& tab ="",uint index=0) ;
    
    virtual void print_equation();
    
    virtual void propag_update(int v =-1);
    
        /// update the list of the dependancies
    virtual void update_list(std::vector<LazyValue*>& vec, int current);
    
    void operator = (const double & d);

    std::string name_;
};

#endif // __LAZYINPUT_HPP__

