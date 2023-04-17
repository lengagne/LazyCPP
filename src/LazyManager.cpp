#include "LazyManager.hpp"

void LazyManager::add_input( LazyInput* in)
{
    inputs_.push_back(in);
}

void LazyManager::add_output( LazyValue* in)
{
    outputs_.push_back(in);
}

LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
{
    if (is_zero(a))
        return b;
    if (is_zero(b))
        return a;    
    
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

LazyValue* LazyManager::add_cosinus( LazyValue* a)
{
    if (is_zero(a))
        return one_;
    
    LazyCosinus* out = new LazyCosinus(a);
    for (int i=0;i<cosinus_.size();i++)
    {
        if (*cosinus_[i] == *out)
        {
            delete out;
            return cosinus_[i];
        }
    }
    cosinus_.push_back(out);
    return out;    
}

LazyValue* LazyManager::add_multiplication( LazyValue* a , LazyValue *b)
{
    if (is_zero(a) || is_zero(b))
        return zero_;
    
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

LazyValue* LazyManager::add_sinus( LazyValue* a)
{    
    LazySinus* out = new LazySinus(a);
    for (int i=0;i<cosinus_.size();i++)
    {
        if (*sinus_[i] == *out)
        {
            delete out;
            return sinus_[i];
        }
    }
    sinus_.push_back(out);
    return out;    
}


LazyValue* LazyManager::add_soustraction( LazyValue* a , LazyValue *b)
{
//     if (is_zero(a))
//         return - b;
    if (is_zero(b))
        return a;    
    
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
    
    // It is not an input it should be a constante.
    in->value_ = value;
        
//     std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" try to set value to unexisting input"<<std::endl;
//     exit(2);
}

double LazyManager::evaluate( LazyVariable& a)
{  
    state_ = true;
    return a.ref_->evaluate(nb_process_);
}

void LazyManager::prepare()
{
    std::cout<<"prepare : there are "<< outputs_.size() << " outputs."<<std::endl;
    re_init_known();
    
    nb_outputs_ = outputs_.size();
    for (int i=0;i<nb_outputs_;i++)
    {
        std::vector<LazyValue*> vec;
        outputs_[i]->add_to_list(vec);
        output_dependances_.push_back(vec);      
        std::cout<<"output("<<i<<") has "<< vec.size() <<" dependances"<<std::endl;
    }
    
}

void LazyManager::re_init_known()
{
    for (int i=0;i<additions_.size();i++)
        additions_[i]->re_init_known();

    for (int i=0;i<soustractions_.size();i++)
        soustractions_[i]->re_init_known();

    for (int i=0;i<multiplications_.size();i++)
        multiplications_[i]->re_init_known();
}

void LazyManager::update_all()
{
    for (int i=0;i<nb_outputs_;i++)
    {
        for (int j =0;j<output_dependances_[i].size();j++)
            output_dependances_[i][j]->compute();
    }
}

double LazyManager::update(uint index)
{
    for (int j =0;j<output_dependances_[index].size();j++)
        output_dependances_[index][j]->compute(); 
    return outputs_[index]->get_value();
}
