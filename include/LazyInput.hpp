#ifndef __LAZYINPUT_HPP__
#define __LAZYINPUT_HPP__

#include "LazyParserCreator.hpp"

class LazyInput : public LazyParserCreator {
public:
    LazyInput(double value, 
              const std::string name="not_defined",
              int id=-1
             ); 
        
    ~LazyInput();
    
    virtual void compute();
    
    virtual LazyCreator* explose();
    
    virtual std::string get_name() const;
    
    virtual std::string file_print( const std::string& varname="x");

    virtual void print( const std::string& tab="") const; 
    
    virtual void print_tree( const std::string& tab ="");

    virtual void update_list(std::vector<LazyCreator*>& vec, int current);
    
    bool operator < ( const LazyInput& in) const;

    std::string name_;
};

#endif // __LAZYINPUT_HPP__

