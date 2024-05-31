#include "LazyAdditionX.hpp"
#include "LazyMultiplicationX.hpp"
#include "LazyMultiplication.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyMultiplicationX::LazyMultiplicationX(std::list<LazyParser*>& a)
{    
//     std::cout<<"LazyMultiplicationX(std::list<LazyValue*>& a)"<<std::endl;
//     for (auto& i : a)
//         std::cout<<"\tLazyMultiplicationX(@"<<i<<") : "<< *i <<std::endl;
            
    typep_ = LAZYP_MULTIPLICATIONX;
    double coeff = 1.0;
    
    LazyAdditionX* addx;
    LazyMultiplicationX* mulx;
    
    LazyParser* simplified;
    
    for(auto& i : a)
    {
        simplified = i->simplify();
//         simplified = i;
        switch (simplified->typep_)
        {
            case(LAZYP_ADDITIONX):
                addx = (LazyAdditionX*) simplified;
                if (addx->p_.size() == 1)
                {
//                     std::cout<<"\t\t Ajout1 de (@"<<i<<") : "<< *i <<std::endl;
                    auto it = addx->p_.begin();
                    coeff *= it->second;
                    p_.push_back(it->first);
                }else
                {
//                     std::cout<<"\t\t Ajout2 de (@"<<i<<") : "<< *i <<std::endl;
                    p_.push_back(addx);
                }
                break;
            case(LAZYP_MULTIPLICATIONX):                
                mulx = (LazyMultiplicationX*)simplified;
                for (auto &it : mulx->p_)
                {
//                     std::cout<<"\t\t Ajout3 de (@"<<it<<") : "<< *it <<std::endl;                    
                    p_.push_back(it);
                }
                break;
                
            default:
//                 std::cout<<"\t\t Ajout4 de (@"<<i<<") : "<< *i <<std::endl;
                p_.push_back(simplified);
        }            
    }    
    // compact modify also p_
//     coeff *= compact(p_);
//     std::cout<<"coeff = "<< coeff <<std::endl;

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
    
//     std::cout<<"coeff = "<< coeff <<std::endl;
    if ( coeff == 0.0)
    {
        p_.clear();
    }else if (coeff != 1.0)
    {
        p_.push_back( LMANAGER.add_parser( new LazyConstant(coeff)));
    }
//     std::cout<<"LazyMultiplicationX::LazyMultiplicationX resultat = "<< *this <<std::endl<<std::endl;
//     print();
//     std::cout<<"***************************************"<<std::endl;
//     std::cout<<"***************************************"<<std::endl;
}

// double LazyMultiplicationX::compact(std::list<LazyParser*> in)
// {
//     
//     std::list<LazyParser*> vec;    
//     for ( auto iter : in)
//     {
//         
//         if ( iter->typep_ == LAZYP_ADDITIONX)
//         {
//             LazyAdditionX* addx = (LazyAdditionX*) iter;
//             if (addx->p_.size() == 1)
//             {
//                 auto it = addx->p_.begin();
//                 cst *= it->second;
//                 vec.push_back(it->first);
//             }
//             
//         }
//         
//         if ( iter->typep_ == LAZYP_MULTIPLICATIONX)
//         {
//             LazyMultiplicationX* AX = (LazyMultiplicationX*) iter;
//             for (auto& iter1 : AX->p_)
//                 vec.push_back( iter1);
//         }else 
//         {
//             vec.push_back(iter);
//         }
//     }    
//     
//     double cst = 1.0;
//     // erase the zero values
//     for (auto it = p_.begin(); it != p_.end(); ) 
//     {
//         if ( iter->typep_ == LAZYP_CONSTANT)
// //         if (it->second == 0.0 || LMANAGER.is_zero( it->first))
//         {
//             cst *= it->value_;
//             it = p_.erase(it);
//         } else {
//             ++it;
//         }
//     }
//     
// 
//     if ( cst == 0.0)
//     {
//         p_.clear();
//     }else if (cst !=1.0)
//     {
//         p_.LMANAGER.add_constant(cst);
//     }
//         p_.clear();
//     }
//     p_.sort(compareLazyParser);
// }

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

double LazyMultiplicationX::get_constant() const
{
    double out = 1.0;
    for (auto& iter : p_)
    {
        if (iter->typep_ == LAZYP_ADDITIONX)
        {
            LazyAdditionX* Ax = (LazyAdditionX*)iter;
            if (Ax->is_double())
                out *= Ax->get_double();
        }
    }
    return out;
}

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
}


bool LazyMultiplicationX::is_zero() const
{
    return (p_.size() ==0);
}


/*
std::string LazyMultiplicationX::get_string( )const 
{
    std::string cmd = "(";
    uint cpt = 0;
    for (auto iter : p_)
    {
        if (cpt++)  cmd = cmd +"*";
        cmd = cmd+ iter->get_string();
    }
    cmd = cmd +")";
    return cmd;
}
*/
void LazyMultiplicationX::print( const std::string& tab) const 
{
    std::cout<<tab<<"LazyMultiplicationX:("<<get_name()<<"): "<<std::endl;
    std::cout<<tab<<"{"<<std::endl;
    for (auto iter : p_)
        iter->print(tab+"\t");
    std::cout<<tab<<"}"<<std::endl;
}   

LazyParser* LazyMultiplicationX::simplify()
{
    for (auto& iter : p_)
    {
        iter->simplify();
//         std::cout<<"iter = "<< *iter <<std::endl;
//         std::cout<<"LMANAGER.get_zero() = "<< *LMANAGER.get_zero() <<std::endl;
        if (LMANAGER.is_zero(iter))
        {
//             std::cout<<"On va avoir zero"<<std::endl;
            return LMANAGER.get_zero();
        }
    }
    
    if (p_.size() == 1)
    {
        auto it = p_.begin();
        return *it;        
    }
    return this;
}

bool LazyMultiplicationX::operator < ( const LazyMultiplicationX& in) const
{
    if ( p_.size() < in.p_.size())  return true;
    if ( p_.size() > in.p_.size())  return false;
    
    auto it = p_.begin();
    auto it2 = in.p_.begin();
    for (; it != p_.end() && it2 != in.p_.end(); ) 
    {
//         if( it->second < it2->second)   return true;
//         if( it->second > it2->second)   return false;
        if( *it < *it2)   return true;
        if( *it > *it2)   return false;
        
        ++it;
        ++it2;
    }
    return false;
//     std::cout<<value_<<" <? "<< in.value_<<std::endl;
//     return (value_ < in.value_);
}

/*
void LazyMultiplicationX::print_equation()
{
    std::cout<<"(";
    uint cpt = 0;
    for (auto iter : p_)
    {
        if(cpt++)
            std::cout<<" * ";   
        iter->print_equation();
    }
    std::cout<<")";
}

void LazyMultiplicationX::propag_update(int v)
{
    update_ = v;
    for (auto iter : p_)
    {
        iter->propag_update(v);
//         update_ = update_ || iter->update_;
    }
}

void LazyMultiplicationX::update_list(std::vector<LazyValue*>& vec, int current)
{
//     std::cerr<<"FILE : "<< __FILE__<<" line : "<< __LINE__<<std::endl;
//     std::cerr<<"THIS FONCTION SHOULD NOT BE CALLED"<<std::endl;
//     std::exit(1234);
    
    if (update_ < current)
    {        
        update_ = current;
        for (auto& iter : p_)
        {
            iter->update_list(vec,current);
        }
        vec.push_back(this);  
    }
    
}  

bool LazyMultiplicationX::operator == (const LazyMultiplicationX& A) const
{
//     if (p_.size() != A.p_.size())
//         return false;
       
    return p_ == A.p_;
}*/
