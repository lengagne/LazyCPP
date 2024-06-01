#ifndef __LAZYCREATOR_HPP__
#define __LAZYCREATOR_HPP__
#include <iostream>
#include <string> 
#include <vector>

typedef enum LazyCreatorType{
    LAZYC_CONSTANT,     //0
    LAZYC_INPUT,        //1
    LAZYC_ADDITION,     //2
    LAZYC_SOUSTRACTION, //3
    LAZYC_MULTIPLICATION,//4
    LAZYC_COSINUS,      //5
    LAZYC_SINUS,        //6
    
} LazyCreatorType;

class LazyCreator
{
public:
    
    virtual void compute() = 0;

    virtual std::string file_print( const std::string& varname ="")=0;
    
    virtual std::string file_subname( const std::string& varname="x")
    {
        return varname + "[" + std::to_string(id_)+"]";
    }    
    
    virtual std::string get_equation( )=0;
    
    virtual double get_value()const
    {
        return value_;
    }
    
    virtual void print_tree( const std::string& tab ="")=0;
    
    virtual void update_list(std::vector<LazyCreator*>& vec, int current)=0;
//     virtual void print_file() const = 0;
    
    friend std::ostream& operator<< (std::ostream& stream, LazyCreator& v);
    
//     std::string name_;
    double value_;
    LazyCreatorType typec_ = LAZYC_CONSTANT;
    int id_ = -1;
    int update_ = -1;
    
protected:        
    
private:
    

};

bool compareLazyCreator(LazyCreator* a,
                        LazyCreator* b);

#endif //  __LAZYADDITION_HPP__
