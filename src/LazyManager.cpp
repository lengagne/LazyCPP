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
            out->print();
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

void LazyManager::affect_value( LazyValue* in, double value)
{
    for (int i=0;i<inputs_.size();i++)
        if(inputs_[i] == in)
        {
            if (state_)
                nb_process_++;              
            state_ = false;
            in->value_ = value;
            in->index_ = nb_process_;
            return;
        }
        
    std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" try to set value to unexisting input"<<std::endl;
    exit(2);
}

double LazyManager::evaluate( LazyVariable& a)
{  
    state_ = true;
    return a.ref_->evaluate(nb_process_);
}
