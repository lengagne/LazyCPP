#include "LazyManager.hpp"
#include <algorithm>


void LazyManager::add_input( LazyInput* in)
{
    inputs_.push_back(in);
}

void LazyManager::add_output( LazyValue* in, uint index, uint rank )
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
        return b;
    }
    if (is_zero(b))
    {
        return a;    
    }
    
    if (contract_add)
    {
        if ( is_addition(a) || is_addition(b))
        {
    //         std::cout<<"addition of addition "<<std::endl;
    //          std::cout<<"a = "; a->print_equation();    std::cout<<"\n";
    //          std::cout<<"b = "; b->print_equation();    std::cout<<"\n";
            std::vector<LazyValue*> vec;
            get_addition(a,vec);
            get_addition(b,vec);

            
            double constante = 0.0;
            for (int i=0;i<vec.size();i++) 
            {
                if (is_constant(vec[i]))
                {
                    constante += vec[i]->value_;
                    vec.erase (vec.begin()+i);
                }
            }            
    //         std::cout<<"on a "<<vec.size()<<" additions imbriquées "<<std::endl;
    // 
    //          for (int i=0;i<vec.size();i++)
    //          {
    //              std::cout<<"\t";   vec[i]->print_equation();   std::cout<<"\n";
    //          }
                    
    //          std::cout<<"sort"<<std::endl;
//             std::sort(vec.begin(),vec.end());        
            LazyValue* out = new LazyConstant(constante);
            for (int i=0;i<vec.size();i++)
                out = new LazyAddition(out,vec[i]);
            return out;         
        }
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
            return constants_[i];
        }
    LazyConstant * out = new LazyConstant(d);
    constants_.push_back(out);
    return out;    
}

LazyValue* LazyManager::add_cosinus( LazyValue* a)
{
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
        return zero_;
    }
    
    if (is_one(a))
    {
        return b;
    }

    if (is_one(b))
    {
        return a;
    }    

    if (is_minus_one(a))
    {
        return add_opposite(b);
    }

    if (is_minus_one(b))
    {
        return add_opposite(a);
    }  
    
    if (is_constant(a) && is_constant(b))
    {
        return add_constant(a->value_ * b-> value_);
    }
    
    if (contract)
    {
        if ( is_multiplication(a) || is_multiplication(b))
        {
    //          std::cout<<"multiplication of multiplication "<<std::endl;
    //          std::cout<<"a = "; a->print_equation();    std::cout<<"\n";
    //          std::cout<<"b = "; b->print_equation();    std::cout<<"\n";
            
            std::vector<LazyValue*> vec;
            uint nb_opposite = 0;
            get_multiplication(a,vec,nb_opposite);
            get_multiplication(b,vec,nb_opposite);
    //          std::cout<<"on a "<<vec.size()<<" multiplication imbriquées avec "<< nb_opposite <<" opposée"<<std::endl;
            
            double constante = 1.0;
            if (nb_opposite%2 == 1)    constante = -1.0;
            for (int i=0;i<vec.size();i++) 
            {
                if (is_constant(vec[i]))
                {
                    constante *= vec[i]->value_;
                    vec.erase (vec.begin()+i);
                }
            }
    //          std::cout<<"constante : "<< constante<<std::endl;
    //          for (int i=0;i<vec.size();i++)
    //          {
    //              std::cout<<"\t";   vec[i]->print_equation();   std::cout<<"\n";
    //          }
    //          std::cout<<"sort"<<std::endl;
//             std::sort(vec.begin(),vec.end());
    //          for (int i=0;i<vec.size();i++)
    //          {
    //              std::cout<<"\t";   vec[i]->print_equation();   std::cout<<"\n";
    //          }         
            
            LazyValue* out = new LazyConstant(constante);
            for (int i=0;i<vec.size();i++)
                out = new LazyMultiplication(out,vec[i]);
            return out;
    //         std::cout<<"a:"<<is_multiplication(a)<<" et b:"<<is_multiplication(b)<<std::endl;
    //         std::cout<<"\t";
    //         a->print_equation();
    //         std::cout<<"\n\t";
    //         b->print_equation();
    //         std::cout<<"\n";
        }    
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
    std::cout<<"Add sinus "<<std::endl;
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

void LazyManager::get_addition(LazyValue * a, std::vector<LazyValue*>& vec)
{
    if (is_addition(a))
    {
        LazyAddition* v = (LazyAddition*) a;
        get_addition(v->a_,vec);
        get_addition(v->b_,vec);
    }else
        vec.push_back(a);
    
}

void LazyManager::get_multiplication(LazyValue * a, std::vector<LazyValue*>& vec, uint &nb_opposite)
{
    if (is_opposite(a))
    {
        nb_opposite++;
        LazyOpposite* v = (LazyOpposite*) a;
        get_multiplication(v->a_,vec,nb_opposite);
    }else 
    if (is_multiplication(a))
    {
        LazyMultiplication* v = (LazyMultiplication*) a;
        get_multiplication(v->a_,vec,nb_opposite);
        get_multiplication(v->b_,vec,nb_opposite);
    }else
        vec.push_back(a);
}

bool LazyManager::is_addition(LazyValue* in) const
{
    for (int i=0;i<additions_.size();i++)
        if( in == additions_[i])
            return true;
    return false;    
}

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

bool LazyManager::is_multiplication( LazyValue* in) const
{
    for (int i=0;i<multiplications_.size();i++)
        if( in == multiplications_[i])
            return true;
    return false;
}

bool LazyManager::is_opposite(LazyValue* in) const
{
{
    for (int i=0;i<opposites_.size();i++)
        if( in == opposites_[i])
            return true;
    return false;
}    
}

void LazyManager::prepare()
{
//     std::cout<<"prepare : there are "<< dependances_.size() << " outputs."<<std::endl;
    uint cpt = 0;
     for (auto iter = dependances_.begin(); iter != dependances_.end(); ++iter)
     {
        re_init_known();
            
        OutDependance& dep = iter->second;
        for (auto idep =dep.outputs.begin(); idep != dep.outputs.end(); idep++)
        {
            std::vector<LazyValue*> vec;
            idep->second->add_to_list(vec);
            dep.output_dependances[idep->first] = vec;
            cpt += vec.size();
            for (int i=0;i<vec.size();i++)
            {
                std::cout<<"\ti="<<i<<" "; vec[i]->print_equation(); std::cout<<"\n";
            }
        }
        
    }    
    std::cout<<"il y a "<< cpt <<" opérations "<<std::endl;
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
    constants_.clear();
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
    for(auto i = dep.output_dependances[cpt].begin(); i != dep.output_dependances[cpt].end();++i)
    {
        (*i)->compute();
    }
    return dep.outputs[cpt]->get_value();
}
