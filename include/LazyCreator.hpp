#ifndef __LAZYCREATOR_HPP__
#define __LAZYCREATOR_HPP__

#include <string> 
#include <vector>

typedef enum LazyCreatorType{
    LAZYC_UNDEFINED,
    LAZYC_CONSTANT,
    LAZYC_INPUT,
    LAZYC_ADDITION,
    LAZYC_SOUSTRACTION,
    LAZYC_MULTIPLICATION,
    
    LAZYC_COSINUS,
    LAZYC_SINUS,
    
} LazyCreatorType;

class LazyCreator
{
public:
    
    virtual void compute() = 0;

    virtual std::string file_print( const std::string& varname="x")=0;
    
    virtual double get_value()const
    {
        return value_;
    }
    
    virtual void update_list(std::vector<LazyCreator*>& vec, int current)=0;
//     virtual void print_file() const = 0;
    
//     std::string name_;
    double value_;
    LazyCreatorType typec_ = LAZYC_UNDEFINED;
    int id_ = -1;
    int update_ = -1;
    
protected:        
    
private:
    

};

bool compareLazyCreator(const LazyCreator* a,
                        const LazyCreator* b);

#endif //  __LAZYADDITION_HPP__
