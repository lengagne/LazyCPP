#ifndef __LAZYMULTIPLICATION_HPP__
#define __LAZYMULTIPLICATION_HPP__

#include "LazyCreator.hpp"

class LazyMultiplication : public LazyCreator {
public:
    LazyMultiplication(LazyCreator* a, LazyCreator* b);
    
    void compute();
    
    virtual std::string file_print( const std::string& varname="x");
    
    void update_list(std::vector<LazyCreator*>& vec, int current);
//     
//     virtual std::string get_string( )const ;
//     
//     virtual void print( const std::string& tab ="",uint index=0);
//     
//     virtual void print_equation();
    LazyCreator* a_;
    LazyCreator* b_;
private:
};

#endif // __LAZYMULTIPLICATION_HPP__
