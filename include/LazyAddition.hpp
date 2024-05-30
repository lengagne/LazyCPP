#ifndef __LAZYADDITION_HPP__
#define __LAZYADDITION_HPP__

#include "LazyCreator.hpp"

class LazyAddition : public LazyCreator 
{
public:
    LazyAddition(LazyCreator* a, LazyCreator* b);
    
//     ~LazyAddition()
//     {
//         
//     }
    
    void compute();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_equation( );
    
    virtual void print_tree( const std::string& tab ="");
    
    void update_list(std::vector<LazyCreator*>& vec, int current);
    
    bool operator < ( const LazyAddition& in) const;
//     
//     virtual std::string get_string( )const ;
//     
//     virtual void print( const std::string& tab ="",uint index=0);
//     
//     virtual void print_equation();
    
// private:
    
    LazyCreator* a_;
    LazyCreator* b_;

};

#endif //  __LAZYADDITION_HPP__
