#ifndef __LAZYVALUE_HPP__
#define __LAZYVALUE_HPP__

#include <iostream>
#include <vector>

typedef enum LazyType{
    LAZYADDITION,
    LAZYADDITIONX,
    LAZYCONSTANT,
    LAZYCOSINUS,
    LAZYMULTIPLICATION,
    LAZYMULTIPLICATIONX,
    LAZYSINUS,
    LAZYSOUSTRACTION,
    LAZYUNDEFINED    
} LazyType;


class LazyValue
{
public:
    
    virtual ~LazyValue(){}

    /// update the list of the dependancies
    virtual void add_to_list(std::vector<LazyValue*>& vec) = 0;
    
    virtual inline void compute()
    {
        
    }
    
    virtual void check_known() = 0;
    
    void define_as_output();
    
    void get_multiplication( std::vector<LazyValue*> vec);
    
    inline double get_value()const
    {
        return value_;
    }
    
    virtual std::string file_print( const std::string& varname="x") = 0;
    
    virtual std::string file_subname( const std::string& varname="x")
    {
        return varname + "[" + std::to_string(id_)+"]";
    }
    
    virtual void print( const std::string& tab ="", uint index=0) = 0;
    
    virtual void print_equation() = 0;
    
    virtual void propag_update()=0;
    
    virtual void re_init_known()
    {
        known_ = false;
    }
    
    void set_time( uint time)
    {
        time_ = time;
    }
    
    friend std::ostream& operator<< (std::ostream& stream, const LazyValue& v)
    {
        stream<<v.value_;
        return stream;
    }
    
    double value_;
    uint time_=0;
    
    // defined if the value is already known;
    bool known_=false;
    bool update_ = false;
    int id_= -1;
    
    LazyType type_ = LAZYUNDEFINED;
};

#endif // __LAZYVALUE_HPP__
