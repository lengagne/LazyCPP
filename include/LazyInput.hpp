#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__

#include "LazyParserCreator.hpp"

class LazyInput : public LazyParserCreator {
public:
    LazyInput(double value, 
              const std::string name="not_defined"); 
        
//     void compact()
//     {
//         
//     }    
    
//     virtual LazyValue* explose()
//     {
//         return this;
//     }
    virtual void compute();
    
    virtual std::string file_print( const std::string& varname="x")
    {
        
    }
    
    virtual void print( const std::string& tab="") const; 
//     
//     virtual std::string get_string( )const ;
// 
//     virtual void print( const std::string& tab ="",uint index=0) ;
//     
//     virtual void print_equation();
//     
//     virtual void propag_update(int v =-1);
//     
//         /// update the list of the dependancies
    virtual void update_list(std::vector<LazyCreator*>& vec, int current);
//     
//     void operator = (const double & d);
// 
    std::string name_;
};

#endif // __LAZYINPUT_HPP__

