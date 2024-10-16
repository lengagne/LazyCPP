#ifndef __LAZYSOUSTRACTION_HPP__
#define __LAZYSOUSTRACTION_HPP__
// 
#include "LazyCreator.hpp"
// 
class LazySoustraction : public LazyCreator 
{
public:
    LazySoustraction(LazyCreator* a, LazyCreator* b);
   
    void compute();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_equation( );
    
    virtual void print_tree( const std::string& tab ="");
        
    void update_list(std::vector<LazyCreator*>& vec, int current);
    
    bool operator < ( const LazySoustraction& in) const;

    LazyCreator* a_;
    LazyCreator* b_;
    
};

#endif // __LAZYSOUSTRACTION_HPP__
