#include "LazyManager.hpp"
#include <algorithm>


LazyManager::LazyManager()
{
    zero_ = new LazyConstant(0.0);   
    one_ = new LazyConstant(1.0);
    minus_one_ = new LazyConstant(-1.0);
    init_basic_constant();
}

LazyValue* LazyManager::add_additionX( LazyValue* a , LazyValue *b)
{
    std::list<LazyValue*> vec;
    if (is_additionX(a))
    {
        LazyAdditionX *A = (LazyAdditionX*) a;
        for (auto iter : A->p_) if (! is_zero(iter))
            vec.push_back(iter);
    }else
        vec.push_back(a);
        
    if (is_additionX(b))
    {
        LazyAdditionX *B = (LazyAdditionX*) b;
        for (auto iter : B->p_)if (! is_zero(iter))
            vec.push_back(iter);    
    }else
        vec.push_back(b);
    
    // creation of the new object
    LazyAdditionX* out = new LazyAdditionX(vec);
    
    // check if does not already exist
    for (auto iter : additionsX_)
        if (*iter == *out)
            return iter;
    additionsX_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_constant( double d)
{
    for (auto iter : constants_)
        if(iter->value_ == d)
        {
            return iter;
        }
    LazyConstant * out = new LazyConstant(d);
    constants_.push_back(out);
    return out;    
}

LazyInput* LazyManager::add_input( const double &a, const std::string& name)
{
    for (auto iter : inputs_)
        if(iter->name_ == name)
        {
            iter->value_ = a;
            return iter;
        }
        
    LazyInput* out = new LazyInput(a,name);
    inputs_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_cosinus( LazyValue* a)
{
    LazyCosinus* out = new LazyCosinus(a);
    // check if does not already exist
    for (auto iter : cosinus_)
        if (*iter == *out)
            return iter;
    cosinus_.push_back(out);
    return out;
}


LazyValue* LazyManager::add_multiplicationX( LazyValue* a , LazyValue *b)
{
    if ( is_zero(a) || is_zero(b))
        return zero_;
    
    if ( is_one(a))
        return b;
    
    if ( is_one(b))
        return a;    
    
    std::list<LazyValue*> vec;
    if (is_multiplicationX(a))
    {
        LazyMultiplicationX *A = (LazyMultiplicationX*) a;
        for (auto iter : A->p_) if (! is_one(iter))
            vec.push_back(iter);
    }else
        vec.push_back(a);
        
    if (is_multiplicationX(b))
    {
        LazyMultiplicationX *B = (LazyMultiplicationX*) b;
        for (auto iter : B->p_) if (! is_one(iter))
            vec.push_back(iter);    
    }else
        vec.push_back(b);
    
    // creation of the new object
    LazyMultiplicationX* out = new LazyMultiplicationX(vec);
    
    // check if does not already exist
    for (auto iter : multiplicationsX_)
        if (*iter == *out)
            return iter;
    multiplicationsX_.push_back(out);
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

void LazyManager::add_output( LazyValue* in, uint index, uint rank )
{
    if (dependances_.find(index) == dependances_.end())
    { // there is no such element, we create it
        dependances_[index] = OutDependance();    
    }    
    dependances_[index].outputs[rank] = in;
}

LazyValue* LazyManager::add_sinus( LazyValue* a)
{
    LazySinus* out = new LazySinus(a);
    // check if does not already exist
    for (auto iter : sinus_)
        if (*iter == *out)
            return iter;
    sinus_.push_back(out);
    return out;
}


LazyValue* LazyManager::add_soustraction( LazyValue* a , LazyValue *b)
{
    if (a == b)
    {
        return zero_;
    }
    
    if (is_zero(b))
    {
        return a;
    }    

    if (is_zero(a))
    {
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

uint LazyManager::get_nb_inputs() const
{
    return inputs_.size();
}

LazyValue* LazyManager::get_zero() const
{
    return zero_;
}

bool LazyManager::is_input( LazyValue* in) const
{
    for (auto iter : inputs_)
        if (iter == in)
            return true;
    return false;
}

bool LazyManager::is_one(LazyValue * in) const
{
    return in == one_;
}

bool LazyManager::is_zero(LazyValue * in) const
{
    return in == zero_;
}

// void LazyManager::add_input( LazyInput* in)
// {
//     inputs_.push_back(in);
// }
// 
// 
// LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
// {
//     if (is_zero(a))
//     {
//         return b;
//     }
//     if (is_zero(b))
//     {
//         return a;    
//     }
//     
// //     if (contract_add)
// //     {
// //         if ( is_addition(a) || is_addition(b) ||  is_additionX(a) || is_additionX(b))
// //         {
// //             std::vector<LazyValue*> vec;
// //             uint nb_opposite = 0;
// //             get_addition(a,vec);
// //             get_addition(b,vec);
// //             
// //             double constante = 0.0;
// //             for (int i=0;i<vec.size();i++) 
// //             {
// //                 if (is_constant(vec[i]))
// //                 {
// //                     constante += vec[i]->value_;
// //                     vec.erase (vec.begin()+i);
// //                 }
// //             }
// //             vec.push_back(new LazyConstant(constante));            
// //             LazyAdditionX* out = new LazyAdditionX(vec);
// //             {
// //                 for (int i=0;i<additionsX_.size();i++)
// //                 {
// //                     if (*additionsX_[i] == *out)
// //                     {
// //                         delete out;
// //                         return additionsX_[i];
// //                     }
// //                 }    
// //                 additionsX_.push_back(out);                
// //             }
// //             return out;
// //         }    
// //     }
//     
//     LazyAddition* out = new LazyAddition(a,b);
//     for (int i=0;i<additions_.size();i++)
//     {
//         if (*additions_[i] == *out)
//         {
//             delete out;
//             return additions_[i];
//         }
//     }
//     additions_.push_back(out);
//     return out;
// }
// 

 /*

LazyValue* LazyManager::add_multiplication( LazyValue* a , LazyValue *b,bool check_contraction )
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
    
//     if (contract && check_contraction)
//     {
//         if ( is_multiplicationX(a) || is_multiplication(a) || is_multiplication(b) || is_multiplicationX(b))
//         {
//             std::vector<LazyValue*> vec;
//             uint nb_opposite = 0;
//             get_multiplication(a,vec,nb_opposite);
//             get_multiplication(b,vec,nb_opposite);
//             
//             double constante = 1.0;
//             if (nb_opposite%2 == 1)    constante = -1.0;
//             for (int i=0;i<vec.size();i++) 
//             {
//                 if (is_constant(vec[i]))
//                 {
//                     constante *= vec[i]->value_;
//                     vec.erase (vec.begin()+i);
//                 }
//             }
//             vec.push_back(new LazyConstant(constante));            
//             LazyMultiplicationX* out = new LazyMultiplicationX(vec);
//             {
//                 for (int i=0;i<multiplicationsX_.size();i++)
//                 {
//                     if (*multiplicationsX_[i] == *out)
//                     {
//                         delete out;
//                         return multiplicationsX_[i];
//                     }
//                 }    
//                 multiplicationsX_.push_back(out);                
//             }
//             return out;
//         }    
//     }
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



// void LazyManager::get_addition(LazyValue * a, std::vector<LazyValue*>& vec)
// {
//     if (is_addition(a))
//     {
//         LazyAddition* v = (LazyAddition*) a;
//         get_addition(v->a_,vec);
//         get_addition(v->b_,vec);
//     }
// //     else 
// //         if (is_additionX(a))
// //     {
// //         LazyAdditionX* v = (LazyAdditionX*) a;
// //         for (int i=0;i<v->p_.size();i++)
// //             get_addition(v->p_[i],vec);        
// //     }
//     else
//         vec.push_back(a);
//     
// }

// void LazyManager::get_multiplication(LazyValue * a, std::vector<LazyValue*>& vec, uint &nb_opposite)
// {
//     if (is_opposite(a))
//     {
//         nb_opposite++;
//         LazyOpposite* v = (LazyOpposite*) a;
//         get_multiplication(v->a_,vec,nb_opposite);
//     }else 
//     if (is_multiplication(a))
//     {
//         LazyMultiplication* v = (LazyMultiplication*) a;
//         get_multiplication(v->a_,vec,nb_opposite);
//         get_multiplication(v->b_,vec,nb_opposite);
//     }
// //     else
// //     if (is_multiplicationX(a))
// //     {
// //         LazyMultiplicationX* v = (LazyMultiplicationX*) a;
// //         for (int i=0;i<v->p_.size();i++)
// //             get_multiplication(v->p_[i],vec,nb_opposite);
// //     }
//     else        
//         vec.push_back(a);
// }

bool LazyManager::is_addition(LazyValue* in) const
{
    for (int i=0;i<additions_.size();i++)
        if( in == additions_[i])
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

// bool LazyManager::is_multiplicationX( LazyValue* in) const
// {
//     for (int i=0;i<multiplicationsX_.size();i++)
//         if( in == multiplicationsX_[i])
//             return true;
//     return false;
// }

bool LazyManager::is_opposite(LazyValue* in) const
{
    for (int i=0;i<opposites_.size();i++)
        if( in == opposites_[i])
            return true;
    return false;    
}

void LazyManager::plot_info() const
{
    std::cout<<"GetLazyInfo()"<<std::endl;
    std::cout<<"There are "<< inputs_.size()<<" inputs."<<std::endl;
    std::cout<<"There are "<< additions_.size()<<" additions."<<std::endl;
    std::cout<<"There are "<< soustractions_.size()<<" soustractions."<<std::endl;
    std::cout<<"There are "<< multiplications_.size()<<" multiplications."<<std::endl;    
    std::cout<<"There are "<< constants_.size()<<" constants."<<std::endl;
    std::cout<<"There are "<< sinus_.size()<<" sinus."<<std::endl;
    std::cout<<"There are "<< cosinus_.size()<<" cosinus."<<std::endl;
//     std::cout<<"There are "<< multiplicationsX_.size()<<" multiplicationsX."<<std::endl;
//     uint cpt_mul = 0;
//     for (int i=0;i< multiplicationsX_.size();i++)
//     {
//         std::cout<<"\tune multiplication de "<< multiplicationsX_[i]->p_.size()<<std::endl;
//         cpt_mul += (multiplicationsX_[i]->p_.size() +1)/2;
//     }
//     std::cout<<"          Pour un total de "<< cpt_mul <<" multiplications"<<std::endl;
    
//     uint cpt_add = 0;
//     std::cout<<"There are "<< additionsX_.size()<<" additionsX."<<std::endl;
//     for (int i=0;i< additionsX_.size();i++)
//     {
//         std::cout<<"\tune addition de "<< additionsX_[i]->p_.size()<<std::endl;    
//         cpt_add += (additionsX_[i]->p_.size()+1)/2;
//     }
//     std::cout<<"          Pour un total de "<< cpt_add <<" additions"<<std::endl;
    
}
*/

void LazyManager::prepare()
{
//     print_all_inputs();
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
        }        
    }
//     print_all_output_equations();
}

void LazyManager::print_all_inputs() const
{
    for (auto iter : inputs_)
    {
        std::cout<<" input : "<< iter->name_<<std::endl;
    }
}

void LazyManager::print_all_output_equations()
{
    for (auto iter = dependances_.begin(); iter != dependances_.end(); ++iter)
    {
        OutDependance& dep = iter->second;
        for (auto idep =dep.outputs.begin(); idep != dep.outputs.end(); idep++)
        {
            std::cout<<"output : ";
            idep->second->print();
            std::cout<<"\n";
        }
    }
}
/*
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
*/
void LazyManager::re_init_known()
{
//     for (auto iter : additions_)   iter->re_init_known();
    for (auto iter : additionsX_)   iter->re_init_known();
    for (auto iter : soustractions_)   iter->re_init_known();
//     for (auto iter : multiplications_)   iter->re_init_known();
    for (auto iter : multiplicationsX_)   iter->re_init_known();
    for (auto iter : cosinus_)   iter->re_init_known();
    for (auto iter : sinus_)   iter->re_init_known();
    for (auto iter : opposites_)   iter->re_init_known();
}

void LazyManager::reset()
{
    inputs_.clear();
    additionsX_.clear();
//     additions_.clear();
    cosinus_.clear();
//     multiplications_.clear();
    multiplicationsX_.clear();
    sinus_.clear();
    soustractions_.clear();
    opposites_.clear();
    constants_.clear();
    init_basic_constant();
    
    dependances_.clear();
}
/*
// void LazyManager::simplify(LazyMultiplicationX* v)
// {
//     bool test = false;
//     do{
//         test = false;
//         for (int i=0;i<v->p_.size();i++)    for (int j=i+1;j<v->p_.size();j++)
//         {
//             LazyMultiplication* out = new LazyMultiplication(v->p_[i],v->p_[j]);
//             for (int k=0;k<multiplications_.size();k++)
//             {
//                 if (*multiplications_[k] == *out)
//                 {
//                     v->p_.erase (v->p_.begin()+j);
//                     v->p_.erase (v->p_.begin()+i);
//                     v->p_.push_back(multiplications_[k]);
//                     test = true;
//                 }
//             }    
//         }        
//     }while(test);
// 
//     std::vector<LazyValue*> vec,vec_new;
//     vec_new = v->p_;
//     do{        
//         vec = vec_new;
//         vec_new.clear();
//         uint nb = vec.size();
//         for (int i=0;i<nb-1;)
//         {
//             vec_new.push_back(add_multiplication(vec[i],vec[i+1], false));
//             i+=2;
//         }
//         if (nb %2 == 1)
//         {
//             vec_new.push_back( vec[nb-1]);
//         }
//         
//     }while (vec_new.size()>2);
//     
//     v->p_ = vec_new;
// }
*/

double LazyManager::update(uint index, uint cpt)
{
    OutDependance& dep = dependances_[index];
    for(auto i = dep.output_dependances[cpt].begin(); i != dep.output_dependances[cpt].end();++i)
    {
        (*i)->compute();        
    }
    return dep.outputs[cpt]->get_value();
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

/////////////////////////////////////////////////////
////////////////////Private functions ///////////////
/////////////////////////////////////////////////////

void LazyManager::init_basic_constant()
{             
    constants_.push_back(zero_);
    constants_.push_back(one_);
    constants_.push_back(minus_one_);        
}

bool LazyManager::is_additionX(LazyValue* in) const
{
    for (auto iter : additionsX_)
        if (iter == in)
            return true;
    return false;    
}

bool LazyManager::is_constant( LazyValue* in) const
{
    for (auto iter : constants_)
        if (iter == in)
            return true;
    return false;    
}
    
bool LazyManager::is_multiplicationX(LazyValue* in) const
{
    for (auto iter : multiplicationsX_)
        if (iter == in)
            return true;
    return false;    
}
