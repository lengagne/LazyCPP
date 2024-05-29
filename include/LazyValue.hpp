#ifndef __LAZYVALUE_HPP__
#define __LAZYVALUE_HPP__

#include <iostream>
#include <vector>
#include <list>

typedef enum LazyType{
    LAZYUNDEFINED,
    LAZYCONSTANT,
    LAZYINPUT,
    LAZYADDITION,
    LAZYADDITIONX,
    LAZYCOSINUS,
    LAZYMULTIPLICATION,
    LAZYMULTIPLICATIONX,
    LAZYSINUS,
    LAZYSOUSTRACTION    
} LazyType;


class LazyValue
{
public:
    
//     virtual ~LazyValue(){}

   
    virtual inline void compute()
    {
        
    }
       
    virtual void compact() = 0;
    
    virtual LazyValue* explose() = 0;
    
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
    
    virtual std::string get_string( ) const = 0;      // FIXME : toutes ces fonctions devraient être const
    
    virtual void print( const std::string& tab ="", uint index=0) = 0;
    
    virtual void print_equation() = 0;
    
    virtual void propag_update(int v =-1)=0;
    
    void set_time( uint time)
    {
        time_ = time;
    }
    
    /// update the list of the dependancies
    virtual void update_list(std::vector<LazyValue*>& vec, int current) = 0;
    
    
    friend std::ostream& operator<< (std::ostream& stream, const LazyValue& v)
    {
        stream<<v.get_string() /*<<"--("<<v.value_<<")"*/;
        return stream;
    }
    
    double value_;
    uint time_=0;
    
    // defined if the value is already known;
    int update_ = -1;
    
    
    bool explosed_ = false;
    bool compacted_ = false;
    int id_= -1;
    
    LazyType type_ = LAZYUNDEFINED;
};

bool compareLazyValue(const LazyValue* a, const LazyValue* b);

bool operator<(const std::list<LazyValue*>& lhs, const std::list<LazyValue*>& rhs);
#endif // __LAZYVALUE_HPP__
