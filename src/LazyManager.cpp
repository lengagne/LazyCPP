#include "LazyManager.hpp"

void LazyManager::add_input( LazyInput* in)
{
    inputs_.push_back(in);
}

void LazyManager::add_output( uint index, LazyValue* in)
{
    if (dependances_.find(index) == dependances_.end())
    { // there is no such element, we create it
        dependances_[index] = OutDependance();    
    }
    
    dependances_[index].outputs.push_back(in);
}

LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
{
//     if (is_zero(a))
//         return b;
//     if (is_zero(b))
//         return a;    
    
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
//     if (is_zero(a))
//         return one_;
    
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
//     if (is_zero(a) || is_zero(b))
//         return zero_;
    
    LazyMultiplication* out = new LazyMultiplication(a,b);
    for (int i=0;i<multiplications_.size();i++)
    {
        if (*multiplications_[i] == *out)
        {
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
/*    if (is_zero(b))
        return a;   */ 
    
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
//             std::cout<<"it is an input"<<std::endl;
//             if (state_)
//                 nb_process_++;              
//             state_ = false;
            in->value_ = value;
//             in->index_ = nb_process_;
            return;
        }
    
    // It is not an input it should be a constant
//     std::cout<<"it is not an input"<<std::endl;
    in->value_ = value;
        
//     std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" try to set value to unexisting input"<<std::endl;
//     exit(2);
}

// double LazyManager::evaluate( LazyVariable& a)
// {  
// //     state_ = true;
//     return a.ref_->evaluate(nb_process_);
// }

void LazyManager::prepare()
{
//     std::cout<<"prepare : there are "<< outputs_.size() << " outputs."<<std::endl;
    
     for (auto iter = dependances_.begin(); iter != dependances_.end(); ++iter)
     {
        re_init_known();
            
        OutDependance& dep = iter->second;
        for (int i=0;i<dep.outputs.size();i++)
        {
            std::vector<LazyValue*> vec;
            dep.outputs[i]->add_to_list(vec);
            dep.output_dependances.push_back(vec);      
        }
    }
}

void LazyManager::print_inputs()
{
    for (int i=0;i<inputs_.size();i++)
        std::cout<<" input("<<i<<") = "<< inputs_[i]->get_value()<<std::endl;
}

void LazyManager::re_init_known()
{
    for (int i=0;i<additions_.size();i++)
        additions_[i]->re_init_known();

    for (int i=0;i<soustractions_.size();i++)
        soustractions_[i]->re_init_known();

    for (int i=0;i<multiplications_.size();i++)
        multiplications_[i]->re_init_known();
    
    for (int i=0;i<cosinus_.size();i++)
        cosinus_[i]->re_init_known();

    for (int i=0;i<sinus_.size();i++)
        sinus_[i]->re_init_known();    
}

void LazyManager::reset()
{
    inputs_.clear();
    additions_.clear();
    cosinus_.clear();
    multiplications_.clear();
    sinus_.clear();
    soustractions_.clear();
    dependances_.clear();
}

void LazyManager::update_all()
{
    for (auto iter = dependances_.begin(); iter != dependances_.end(); ++iter)
    {
        OutDependance& dep = iter->second;
        for (int i=0;i<dep.outputs.size();i++)
        {
            for (int j =0;j<dep.output_dependances[i].size();j++)
                dep.output_dependances[i][j]->compute();
        }
    }
}

double LazyManager::update(uint index, uint cpt)
{
    
    OutDependance& dep = dependances_[index];
//     for (int i=0;i<dep.outputs.size();i++)
//     {
        for (int j =0;j<dep.output_dependances[cpt].size();j++)
            dep.output_dependances[cpt][j]->compute();
//     }
        
//     std::cout<<"Update index = "<< index <<std::endl;
//     for (int j =0;j<output_dependances_[index].size();j++)
//     {
//         output_dependances_[index][j]->compute(); 
// // //         std::cout<<"update with "<< output_dependances_[index][j]->get_value()<<std::endl;
//     }
//     outputs_[index]->print();
    return dep.outputs[cpt]->get_value();
}
