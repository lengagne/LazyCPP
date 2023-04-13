#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__

#include "LazyCPP.hpp"
#include <vector>

struct InputDependancies
{
    std::vector<LazyInput*> inputs_;
    uint index_;
};


class LazyManager
{
public:
    LazyManager(){}
    
    virtual ~LazyManager(){}
    
    void add_input( LazyInput* in);
    
    LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_soustraction( LazyValue* a , LazyValue *b);
    
    LazyValue* add_multiplication( LazyValue* a , LazyValue *b);
    
    void affect_value( LazyValue* in, double value);
    
    double evaluate( LazyVariable&a);
    
    friend void GetLazyInfo();
    
    friend void PrintGraph(LazyVariable& in);
    
private:

    std::vector<LazyInput*> inputs_;    
    std::vector<LazyAddition*> additions_;
    std::vector<LazySoustraction*> soustractions_;
    std::vector<LazyMultiplication*> multiplications_;
    
    bool state_ = true;    // 0 for assignation, 1 for evaluation
    uint nb_process_=0;
    
};

void GetLazyInfo();

void PrintGraph(LazyValue* in);


#endif // __LAZYMANAGER_HPP__
