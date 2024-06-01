#include "LazyAdditionX.hpp"
#include "LazyMultiplicationX.hpp"
#include "LazyMultiplication.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyMultiplicationX::LazyMultiplicationX(std::list<LazyParser*>& a)
{    
//     std::cout<<"debut mul("<<this<<")"<<std::endl;
//     for(auto&i : a)
//         std::cout<<"LazyMultiplicationX  a = "<< *i<<std::endl;
    typep_ = LAZYP_MULTIPLICATIONX;
    double coeff = 1.0;
    
    LazyAdditionX* addx;
    LazyMultiplicationX* mulx;
    
    LazyParser* simplified;
    
    for(auto& i : a)
    {
        simplified = i->simplify();
        switch (simplified->typep_)
        {
            case(LAZYP_ADDITIONX):
                addx = (LazyAdditionX*) simplified;
                if (addx->p_.size() == 1)
                {
                    auto it = addx->p_.begin();
                    coeff *= it->second;
                    p_.push_back(it->first);
                }else
                {
                    p_.push_back(addx);
                }
                break;
            case(LAZYP_MULTIPLICATIONX):                
                mulx = (LazyMultiplicationX*)simplified;
                for (auto &it : mulx->p_)
                {
                    p_.push_back(it);
                }
                break;
                
            default:
                p_.push_back(simplified);
        }            
    }    

    // erase the zero values
    for (auto it = p_.begin(); it != p_.end(); ) 
    {
        if ( (*it)->typep_ == LAZYP_CONSTANT)
        {
            coeff *= ((LazyConstant*)(*it))->value_;
            it = p_.erase(it);
        } else {
            ++it;
        }
    }
    
    if ( coeff == 0.0)
    {
        p_.clear();
    }else if (coeff != 1.0)
    {
        p_.push_back( LMANAGER.add_parser( new LazyConstant(coeff)));
    }
//     std::cout<<"Fin mul("<<this<<")"<<std::endl;
//     print();
//     std::cout<< *this <<std::endl<<std::endl<<std::endl;
}

LazyParser* LazyMultiplicationX::do_simplification()
{
    
    for (auto& iter : p_)
    {
        iter->simplify();
        if (LMANAGER.is_zero(iter))
        {
            return LMANAGER.get_zero();
        }
    }
    
    if (p_.size() == 1)
    {
        auto it = p_.begin();
        return *it;        
    }
    
    std::list<LazyParser*> a;
    double coeff = 1.0;
    for (auto& iter : p_)
    {
        LazyParser* s = iter->simplify();
        switch (s->typep_)
        {
            case(LAZYP_CONSTANT):
                
                if( ((LazyConstant*) s)->value_ == 0.0)
                    return LMANAGER.get_zero();
                
                coeff *= ((LazyConstant*) s)->value_;
                break;
            
            case(LAZYP_MULTIPLICATIONX):
                for (auto& i : ((LazyMultiplicationX*) s)->p_)
                {
                    a.push_back(i);
                }
                break; 
                
            case(LAZYP_INPUT):
            case(LAZYP_COSINUS):
            case(LAZYP_SINUS):
            case(LAZYP_ADDITIONX):
                a.push_back(s);
                break;            
            
            default:
                std::cerr<<"In file "<< __FILE__<<" at line "<< __LINE__ <<" the type "<< s->typep_ <<" is not implemented yet."<<std::endl;
                a.push_back(s);
        }
        
    }    
    if (coeff != 1.0)
    {
        a.push_back( LMANAGER.add_constant_parser(coeff));
    }
    LazyParser* out = new LazyMultiplicationX(a);
    return out;
}


LazyCreator* LazyMultiplicationX::explose()
{
    if (explosed_ == nullptr)
    {       
        
        int cpt = 0;
        for (auto& iter : p_)  // if ( !LMANAGER.is_one(iter))
        {
            if (cpt++ == 0)
            {
                explosed_ = iter->explose();
            }else
            {
                explosed_ = LMANAGER.add_multiplication(explosed_,iter->explose());
            }
        }
        
        if (explosed_ == nullptr)
        {
            explosed_ = LMANAGER.get_zero()->explose();
            return explosed_;
        }
        
    }      
    return explosed_;    
}

// double LazyMultiplicationX::get_constant() const
// {
//     double out = 1.0;
//     for (auto& iter : p_)
//     {
//         if (iter->typep_ == LAZYP_ADDITIONX)
//         {
//             LazyAdditionX* Ax = (LazyAdditionX*)iter;
//             if (Ax->is_double())
//                 out *= Ax->get_double();
//         }
//     }
//     return out;
// }

std::string LazyMultiplicationX::get_name() const
{
    std::string cmd = "{";
    int cpt = 0;
    for (auto&i : p_)
    {
        if (cpt++)  cmd +="*";
        cmd += i->get_name();
    }
    cmd += "}";
    return cmd;
}
/*
LazyParser* LazyMultiplicationX::get_without_constant() const
{
    std::list<LazyParser*> vec;
    for (auto& iter : p_)
    {
        if (iter->typep_ != LAZYP_ADDITIONX || ! ((LazyAdditionX*)iter)->is_double())
        {
            vec.push_back(iter);
        }
    }
    
    if (vec.size() == 1)
        return new LazyAdditionX(1.0,vec.front());
    
    return new LazyMultiplicationX(vec);
}*/


bool LazyMultiplicationX::is_zero() const
{
    return (p_.size() ==0);
}

void LazyMultiplicationX::print( const std::string& tab) const 
{
    std::cout<<tab<<"LazyMultiplicationX:("<<get_name()<<"): "<<std::endl;
    std::cout<<tab<<"{"<<std::endl;
    for (auto iter : p_)
        iter->print(tab+"\t");
    std::cout<<tab<<"}"<<std::endl;
}   

bool LazyMultiplicationX::operator < ( const LazyMultiplicationX& in) const
{
    if ( p_.size() < in.p_.size())  return true;
    if ( p_.size() > in.p_.size())  return false;
    
    auto it = p_.begin();
    auto it2 = in.p_.begin();
    for (; it != p_.end() && it2 != in.p_.end(); ) 
    {
        if( *it < *it2)   return true;
        if( *it > *it2)   return false;
        
        ++it;
        ++it2;
    }
    return false;
}
