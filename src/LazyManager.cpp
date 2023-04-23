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
    LazyValue* check = check_addition(a,b);
    if (check)
        return check;    
    
    std::list<LazyValue*> vec;
    if (is_additionX(a))
    {
        LazyAdditionX *A = (LazyAdditionX*) a;
        for (auto& iter : A->p_) if (! is_zero(iter))
            vec.push_back(iter);
    }else
        vec.push_back(a);
        
    if (is_additionX(b))
    {
        LazyAdditionX *B = (LazyAdditionX*) b;
        for (auto& iter : B->p_)if (! is_zero(iter))
            vec.push_back(iter);    
    }else
        vec.push_back(b);
    
    // creation of the new object
    LazyAdditionX* out = new LazyAdditionX(vec);
    
    // check if does not already exist
    for (auto& iter : additionsX_)
        if (*iter == *out)
            return iter;
    additionsX_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_constant( double d)
{
    for (auto& iter : constants_)
        if(iter->value_ == d)
        {
            return iter;
        }
    LazyConstant * out = new LazyConstant(d);
    constants_.push_back(out);
    return out;    
}

LazyValue* LazyManager::add_cosinus( LazyValue* a)
{
    LazyCosinus* out = new LazyCosinus(a);
    // check if does not already exist
    for (auto& iter : cosinus_)
        if (*iter == *out)
            return iter;
    cosinus_.push_back(out);
    return out;
}

LazyInput* LazyManager::add_input( const double &a, const std::string& name)
{
    for (auto& iter : inputs_)
        if(iter->name_ == name)
        {
            iter->value_ = a;
            return iter;
        }
        
    LazyInput* out = new LazyInput(a,name);
    inputs_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_multiplicationX( LazyValue* a , LazyValue *b)
{
    LazyValue* check = check_multiplication(a,b);
    if (check)
        return check;
    
    std::list<LazyValue*> vec;
    if (is_multiplicationX(a))
    {
        LazyMultiplicationX *A = (LazyMultiplicationX*) a;
        for (auto& iter : A->p_) if (! is_one(iter))
            vec.push_back(iter);
    }else
        vec.push_back(a);
        
    if (is_multiplicationX(b))
    {
        LazyMultiplicationX *B = (LazyMultiplicationX*) b;
        for (auto& iter : B->p_) if (! is_one(iter))
            vec.push_back(iter);    
    }else
        vec.push_back(b);
    
    return add_multiplicationX(vec);
}

LazyValue* LazyManager::add_output( LazyValue* in, uint index, uint rank )
{
    // FIXME : on ne dit rien si ca existe deja
    if (dependances_.find(index) == dependances_.end())
    { // there is no such element, we create it
        dependances_[index] = Dependance(index);    
    }   

    LazyValue *output = explose(compact(in));
    dependances_[index].add_suboutput(output,rank);
    return output;
}

LazyValue* LazyManager::add_sinus( LazyValue* a)
{
    LazySinus* out = new LazySinus(a);
    // check if does not already exist
    for (auto& iter : sinus_)
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
        return add_multiplicationX(b,minus_one_);
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

uint LazyManager::affect()
{
    affect_ = true;
    return counter_;
}

LazyValue* LazyManager::check_addition( LazyValue*a , LazyValue*b)
{            
    if ( is_zero(a))
        return b;
    
    if ( is_zero(b))
        return a;

    if (is_minus_one(a))
    {
        return add_soustraction(b,a);
    }

    if (is_minus_one(b))
    {
        return add_soustraction(a,b);
    }  
    
    return 0;
}


LazyValue* LazyManager::check_multiplication( LazyValue*a , LazyValue*b)
{        
    if ( is_zero(a) || is_zero(b))
        return zero_;
    
    if ( is_one(a))
        return b;
    
    if ( is_one(b))
        return a;
    
    if (is_constant(a) && is_constant(b))
    {
        return add_constant( a->value_*b->value_);
    }
    
    return 0;
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
    for (auto& iter : inputs_)
        if (iter == in)
            return true;
    return false;
}

bool LazyManager::is_minus_one(LazyValue * in) const
{
    return in == minus_one_;
}    

bool LazyManager::is_one(LazyValue * in) const
{
    return in == one_;
}

bool LazyManager::is_zero(LazyValue * in) const
{
    return in == zero_;
}

void LazyManager::prepare()
{
//     print_all_inputs();
    uint cpt = 0;
    for (auto& iter : dependances_)
    {
        re_init_known();  
        iter.second.compute_dependances();
/*        
        OutDependance& dep = iter->second;
        for (auto idep =dep.outputs.begin(); idep != dep.outputs.end(); idep++)
        {
            std::vector<LazyValue*> vec;
            idep->second->add_to_list(vec);
            dep.output_dependances[idep->first] = vec;
            cpt += vec.size();
        }        */
    }
//     print_all_output_equations();
}

void LazyManager::print_all_inputs() const
{
    for (auto& iter : inputs_)
    {
        std::cout<<" input : "<< iter->name_<<std::endl;
    }
}

void LazyManager::print_all_output_equations()
{
//     for (auto iter = dependances_.begin(); iter != dependances_.end(); ++iter)
    for (auto& iter : dependances_)
    {
        iter.second.print();
//         Dependance& dep = iter.second;
//         for (auto idep =dep.outputs.begin(); idep != dep.outputs.end(); idep++)
//         {
//             std::cout<<"output : ";
//             idep->second->print();
//             std::cout<<"\n";
//         }
    }
}

void LazyManager::re_init_known()
{
//     for (auto iter : additions_)   iter->re_init_known();
    for (auto& iter : additionsX_)   iter->re_init_known();
    for (auto& iter : soustractions_)   iter->re_init_known();
//     for (auto& iter : multiplications_)   iter->re_init_known();
    for (auto& iter : multiplicationsX_)   iter->re_init_known();
    for (auto& iter : cosinus_)   iter->re_init_known();
    for (auto& iter : sinus_)   iter->re_init_known();
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
    constants_.clear();
    init_basic_constant();
    counter_ = 0;
    affect_ = false;
    
    
    dependances_.clear();
}

double LazyManager::update(uint index, uint cpt)
{
    if (affect_)
    {        
        affect_ = false;        
        detect_input_change();
        counter_ ++;
    }
    
    return dependances_[index].update(cpt,current_change_);
//     // on regarde si on a deja eu le changement 
//     std::map<Change,OutDependance>::iterator it = memory_computation_.find(current_change_);
//     if ( it==memory_computation_.end())
//     {
//         std::cout<<"Structure non encore vue : on l'ajoute"<<std::endl;
//         memory_computation_[current_change_] = OutDependance();
//     }else
//     {
//         std::cout<<"Strucutre deja vue "<<std::endl;
//     }
    
//     OutDependance& dep = dependances_[index];
//     for(auto i = dep.output_dependances[cpt].begin(); i != dep.output_dependances[cpt].end();++i)
//     {
//         (*i)->compute();        
//     }
//     return dep.outputs[cpt]->get_value();
}

void LazyManager::update_all()
{
    if (affect_)
    {
        counter_ ++;
        affect_ = false;
    }

    // FIXME
//     for (auto& iter = dependances_.begin(); iter != dependances_.end(); ++iter)
//     {
//         OutDependance& dep = iter->second;
//         for (int i=0;i<dep.outputs.size();i++)
//         {
//             for (int j =0;j<dep.output_dependances[i].size();j++)
//                 dep.output_dependances[i][j]->compute();
//         }
//     }
}

/////////////////////////////////////////////////////
////////////////////Private functions ///////////////
/////////////////////////////////////////////////////

LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
{
    LazyValue* check = check_addition(a,b);
    if (check)
        return check;
    
    LazyAddition* out = new LazyAddition(a,b);
    for (auto& iter : additions_)
    {
        if (*iter == *out)
        {
            delete out;
            return iter;
        }
    }
    additions_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_additionX( std::list<LazyValue*> v)
{
    // creation of the new object
    LazyAdditionX* out = new LazyAdditionX(v);
    
    // check if does not already exist
    for (auto& iter : additionsX_)
        if (*iter == *out)
            return iter;
    additionsX_.push_back(out);
    return out;    
}

LazyValue* LazyManager::add_multiplicationX( std::list<LazyValue*> v)
{
    // creation of the new object
    LazyMultiplicationX* out = new LazyMultiplicationX(v);
    
    // check if does not already exist
    for (auto& iter : multiplicationsX_)
        if (*iter == *out)
            return iter;
    multiplicationsX_.push_back(out);
    return out;    
}

LazyValue* LazyManager::add_multiplication( LazyValue* a , LazyValue *b)
{
    LazyValue* check = check_multiplication(a,b);
    if (check)
        return check;
    
    LazyMultiplication* out = new LazyMultiplication(a,b);
    for (auto& iter : multiplications_)
    {
        if (*iter == *out)
        {
            delete out;
            return iter;
        }
    }    
    multiplications_.push_back(out);
    return out;
}

LazyValue* LazyManager::compact( LazyValue* a)
{   
    if ( is_additionX(a))
    {
        return compact_additionX( (LazyAdditionX*) a);
    }
    
    if ( is_multiplicationX(a))
    {
        return compact_multiplicationX( (LazyMultiplicationX*) a);
    }    
    return a;
}

LazyValue * LazyManager::compact_additionX (LazyAdditionX *a )
{
    LazyValue* cst = zero_;
    std::list<LazyValue*> vec;
    
    for ( auto iter : a->p_)
    {
        LazyValue * tmp = compact(iter);
 
        if ( is_constant(tmp))
        {
            cst = add_addition(cst,tmp);
        }else if (is_additionX(iter))
        {
            LazyAdditionX *v = (LazyAdditionX*) iter;
            for (auto& iter1 : v->p_)
                vec.push_back( compact(iter1));
        }else 
        {
//         if (is_opposite(tmp))
//         {
//             cst = add_multiplication(cst,minus_one_);
//             LazyOpposite * v = (LazyOpposite*) tmp;
//             vec.push_back( compact(v->a_));
//         }
//         else
            vec.push_back( compact(tmp));
        }
    }
    if ( !is_zero(cst))
        vec.push_back(cst);
    
    return add_additionX(vec);
    
}

LazyValue * LazyManager::compact_multiplicationX (LazyMultiplicationX *a )
{
    LazyValue* cst = one_;
    std::list<LazyValue*> vec;
    
    for ( auto iter : a->p_)
    {     
        if ( is_constant(iter))
        {
            cst = add_multiplication(cst,iter);
        }else if (is_multiplicationX(iter))
        {
            LazyMultiplicationX *v = (LazyMultiplicationX*) iter;
            for (auto& iter1 : v->p_)
                vec.push_back( compact(iter1));
        }
        else
            vec.push_back( compact(iter));
    }
    if ( !is_one(cst))
        vec.push_back(cst);
    
    return add_multiplicationX(vec);
    
//     return a;
}

void LazyManager::detect_input_change()
{
//     std::cout<<" time = "<< counter_<<std::endl;
//     current_change_.clear();
//     for (auto& iter : inputs_)
//     {
//         if (counter_ == iter->time_)
//         {
//             std::cout<<" changement pour = "<< iter->name_<<std::endl;
//             current_change_.push_back(iter);
//         }else
//         {
// //             std::cout<<" idem pour = "<< iter->name_<<std::endl;
//         }        
//     }
}

LazyValue * LazyManager::explose( LazyValue * in)
{
    if (is_additionX(in))
    {
        LazyAdditionX* v = (LazyAdditionX*) in;
        LazyValue* m = zero_;
        for (auto& iter : v->p_)
            m = add_addition( m,explose(iter));
        return m;
    }    

    if (is_cosinus(in))
    {
        LazyCosinus* v = (LazyCosinus*) in;
        return add_cosinus( explose(v->a_));
    }
    
    if (is_constant(in))   return in;

    if (is_input(in))   return in;

    
    if (is_multiplicationX(in))
    {
        LazyMultiplicationX* v = (LazyMultiplicationX*) in;
        LazyValue* m = one_;
        for (auto& iter : v->p_)
            m = add_multiplication( m,explose(iter));
        return m;
    }
    
    if (is_sinus(in))
    {
        LazySinus* v = (LazySinus*) in;
        return add_sinus( explose(v->a_));
    }
            
    std::cerr<<"Error in "<< __FILE__<<" at line : "<< __LINE__<<" the case of value ";
    in->print();
    exit(63);
}

void LazyManager::init_basic_constant()
{             
    constants_.push_back(zero_);
    constants_.push_back(one_);
    constants_.push_back(minus_one_);        
}

bool LazyManager::is_additionX(LazyValue* in) const
{
    for (auto& iter : additionsX_)
        if (iter == in)
            return true;
    return false;    
}

bool LazyManager::is_constant( LazyValue* in) const
{
    for (auto& iter : constants_)
        if (iter == in)
            return true;
    return false;    
}

bool LazyManager::is_cosinus( LazyValue* in) const
{
    for (auto& iter : cosinus_)
        if (iter == in)
            return true;
    return false;    
}

bool LazyManager::is_multiplication( LazyValue* in) const
{
    for (auto& iter : multiplications_)
        if (iter == in)
            return true;
    return false;    
}

bool LazyManager::is_multiplicationX(LazyValue* in) const
{
    for (auto& iter : multiplicationsX_)
        if (iter == in)
            return true;

    return false;    
}

bool LazyManager::is_sinus( LazyValue* in) const
{
    for (auto& iter : sinus_)
        if (iter == in)
            return true;
    return false;    
}
