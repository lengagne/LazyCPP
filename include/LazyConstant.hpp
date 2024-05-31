#ifndef __LAZYCONSTANT_HPP__
#define __LAZYCONSTANT_HPP__

#include "LazyParserCreator.hpp"
#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 20)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

class LazyConstant : public LazyParserCreator {
public:
    LazyConstant(double value);
    
    ~ LazyConstant();
    
    void compute();
    
    virtual LazyCreator* explose();
    
    virtual std::string file_subname( const std::string& varname="x")
    {
        return std::to_string( value_);
    }
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string get_name() const;
    
    virtual void print( const std::string& tab="") const; 
    
    virtual void print_tree( const std::string& tab ="");
    
    void update_list(std::vector<LazyCreator*>& vec, int current);      
    
    bool operator < ( const LazyConstant& in) const;
//     void compact()
//     {
//         
//     }
//     
//     LazyValue* explose()
//     {
//         return this;
//     }
//     
//     virtual std::string get_string( )const ;
//     
//     virtual std::string file_print( const std::string& varname="x");
//     
//     virtual std::string file_subname( const std::string& varname="x");
//     
//     virtual void print( const std::string& tab ="",uint index=0) ;
// 
//     virtual void print_equation();
//     
//     virtual void propag_update(int v=-1);
//        
//         /// update the list of the dependancies
//     virtual void update_list(std::vector<LazyValue*>& vec, int current);
//     
//     void operator = (const double & d);
//         
// private:
};

#endif // __LAZYCONSTANT_HPP__
