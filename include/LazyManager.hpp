#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__

#include "LazyCPP.hpp"
#include <vector>

class LazyManager
{
public:
    LazyManager(){}
    
    virtual ~LazyManager(){}
    
    void add_input( LazyInput* in);
    
    LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_soustraction( LazyValue* a , LazyValue *b);
    
    LazyValue* add_multiplication( LazyValue* a , LazyValue *b);
    
    
    
    friend void GetLazyInfo();
    
private:

    std::vector<LazyInput*> inputs_;    
    std::vector<LazyAddition*> additions_;
    std::vector<LazySoustraction*> soustractions_;
    std::vector<LazyMultiplication*> multiplications_;
    
};

void GetLazyInfo();



#endif // __LAZYMANAGER_HPP__
