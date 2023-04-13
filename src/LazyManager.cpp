#include "LazyManager.hpp"

void LazyManager::add_input( LazyInput* in)
{
    inputs_.push_back(in);
}

LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
{
    LazyAddition* out = new LazyAddition(a,b);
    for (int i=0;i<additions_.size();i++)
    {
        if (*additions_[i] == *out)
        {
            delete out;
            return additions_[i];
        }
    }
    additions_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_multiplication( LazyValue* a , LazyValue *b)
{
    LazyMultiplication* out = new LazyMultiplication(a,b);
    for (int i=0;i<multiplications_.size();i++)
    {
        if (*multiplications_[i] == *out)
        {
            std::cout<<"remove one multiplication"<<std::endl;
            out->print();
            multiplications_[i]->print();
            std::cout<<"*************************"<<std::endl;
            delete out;
            return multiplications_[i];
        }
    }    
    multiplications_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_soustraction( LazyValue* a , LazyValue *b)
{
    LazySoustraction* out = new LazySoustraction(a,b);
    for (int i=0;i<soustractions_.size();i++)
    {
        if (*soustractions_[i] == *out)
        {
            delete out;
            return soustractions_[i];
        }
    }        
    soustractions_.push_back(out);
    return out;
}
