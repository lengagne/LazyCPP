#ifndef __LAZYCONSTANT_HPP__
#define __LAZYCONSTANT_HPP__

#include "LazyValue.hpp"
#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 30)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

class LazyConstant : public LazyValue {
public:
    LazyConstant(double value);
    
    /// update the list of the dependancies
    virtual void add_to_list(std::vector<LazyValue*>& vec);
        
    virtual void check_known();
    
    virtual std::string file_print( const std::string& varname="x");
    
    virtual std::string file_subname( const std::string& varname="x");
    
    virtual void print( const std::string& tab ="",uint index=0) ;

    virtual void print_equation();
    
    virtual void propag_update();
    
    virtual void re_init_known();
    
    void operator = (const double & d);
        
private:
};


#endif // __LAZYCONSTANT_HPP__

