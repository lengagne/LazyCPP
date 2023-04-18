#include "LazyManager.hpp"

void LazyManager::add_input( LazyInput* in)
{
    inputs_.push_back(in);
}

void LazyManager::add_output( LazyValue* in, uint index, uint rank )
// void LazyManager::add_output( uint index, LazyValue* in)
{
    if (dependances_.find(index) == dependances_.end())
    { // there is no such element, we create it
        dependances_[index] = OutDependance();    
    }
    
    dependances_[index].outputs[rank] = in;
}

LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
{
    if (is_zero(a))
    {
//         std::cout<<"Simplify Addition with zero"<<std::endl;
        return b;
    }
    if (is_zero(b))
    {
//         std::cout<<"Simplify Addition with zero"<<std::endl;
        return a;    
    }
    
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

LazyValue* LazyManager::add_constant( double d)
{
    for (int i=0;i<constants_.size();i++)
        if(constants_[i]->value_ == d)
        {
//             std::cout<<"Return existing constant d ="<<d <<"\t"<< constants_[i] <<std::endl;
            return constants_[i];
        }
    LazyConstant * out = new LazyConstant(d);
//     std::cout<<"Return new constant d = "<<d<<"\t"<< out<<std::endl;
    constants_.push_back(out);
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
    if (is_zero(a) || is_zero(b))
    {
//         std::cout<<"Simplify Multiplication with zero"<<std::endl;
        return zero_;
    }
    
    if (is_one(a))
    {
//         std::cout<<"Simplify Multiplication by one"<<std::endl;
        return b;
    }

    if (is_one(b))
    {
//         std::cout<<"Simplify Multiplication by one"<<std::endl;
        return a;
    }    

    if (is_minus_one(a))
    {
//         std::cout<<"Simplify Multiplication by minus one"<<std::endl;
        return add_opposite(b);
    }

    if (is_minus_one(b))
    {
//         std::cout<<"Simplify Multiplication by minus one"<<std::endl;
        return add_opposite(a);
    }  
    
    if (is_constant(a) && is_constant(b))
    {
        std::cout<<"a et b sont constants"<<std::endl;
        return add_constant(a->value_ * b-> value_);
    }
    
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

LazyValue* LazyManager::add_opposite(LazyValue* a )
{
    LazyOpposite* out = new LazyOpposite(a);
    for (int i=0;i<opposites_.size();i++)
    {
        if (*opposites_[i] == *out)
        {
            delete out;
            return opposites_[i];
        }
    }
    opposites_.push_back(out);
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
    if (a == b)
    {
//         std::cout<<"soustraction par soi même, renvoi zéro"<<std::endl;
        return zero_;
    }
    
    if (is_zero(b))
    {
//         std::cout<<"soustraction par zéro"<<std::endl;
        return a;
    }    

    if (is_zero(a))
    {
//         std::cout<<"soustraction de zéro"<<std::endl;
        return add_opposite(b);
    }    
    
    
    
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

// void LazyManager::affect_value( LazyValue* in, double value)
// {
//     if (is_input(in))
//     {
//         in->value_ = value;
//         return;
//     }
//     
//     std::cout<<" quoi faire ? "<< std::endl;
//     in->value_ = value;
//         
// //     std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" try to set value to unexisting input"<<std::endl;
// //     exit(2);
// }

// double LazyManager::evaluate( LazyVariable& a)
// {  
// //     state_ = true;
//     return a.ref_->evaluate(nb_process_);
// }


bool LazyManager::is_constant( LazyValue* in) const
{
    for (int i=0;i<constants_.size();i++)
        if( in == constants_[i])
            return true;
    return false;
}
    

bool LazyManager::is_input( LazyValue* in) const
{
    for (int i=0;i<inputs_.size();i++)
        if( in == inputs_[i])
            return true;
    return false;
}

void LazyManager::prepare()
{
//     std::cout<<"prepare : there are "<< dependances_.size() << " outputs."<<std::endl;
     for (auto iter = dependances_.begin(); iter != dependances_.end(); ++iter)
     {
        re_init_known();
            
        OutDependance& dep = iter->second;
        for (auto idep =dep.outputs.begin(); idep != dep.outputs.end(); idep++)
        {
            std::vector<LazyValue*> vec;
            idep->second->add_to_list(vec);
            dep.output_dependances[idep->first] = vec;
//             std::cout<<"input "<< iter->first<<" rank "<< idep->first <<" there are "<< vec.size() <<" computations"<<std::endl;
        }
        
//         for (int i=0;i<dep.outputs.size();i++)
//         {
//             
//            
//             dep.output_dependances.push_back(vec);      
//         }
    }
}

void LazyManager::print_inputs()
{
    for (int i=0;i<inputs_.size();i++)
        std::cout<<" input("<<i<<") = "<< inputs_[i]->get_value()<<std::endl;
}

void LazyManager::print_output_graph(uint index, uint cpt)
{
    std::cout<<"index = "<< index <<"\tcpt = " << cpt <<std::endl;
    
    std::cout<<"ZERO : ";
    zero_->print();
    
    std::cout<<"ONE : ";
    one_->print();
    
    std::cout<<"MINUS ONE : ";
    minus_one_->print();    
    
    OutDependance& dep = dependances_[index];
    dep.outputs[cpt]->print();            
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

    for (int i=0;i<opposites_.size();i++)
        opposites_[i]->re_init_known();   
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
    opposites_.clear();
    init_basic_constant();
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
