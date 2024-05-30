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
    
    for(auto& i : a)
    {
        switch (i->typep_)
        {
            case(LAZYP_ADDITIONX):
                addx = (LazyAdditionX*) i;
                if (addx->is_double())
                {
//                     std::cout<<"\t\t Ajout1 de (@"<<i<<") : "<< *i <<std::endl;
                    coeff *= addx->get_double();
                }else
                {
//                     std::cout<<"\t\t Ajout2 de (@"<<i<<") : "<< *i <<std::endl;
                    p_.push_back(i);
                }
                break;
            case(LAZYP_MULTIPLICATIONX):                
                mulx = (LazyMultiplicationX*)i;
                for (auto &it : mulx->p_)
                {
//                     std::cout<<"\t\t Ajout3 de (@"<<it<<") : "<< *it <<std::endl;                    
                    p_.push_back(it);
                }
                break;
                
            default:
//                 std::cout<<"\t\t Ajout4 de (@"<<i<<") : "<< *i <<std::endl;
                p_.push_back(i);
        }            
    }    
    coeff *= compact(p_);
    if (coeff != 1.0)
    {
        p_.push_back( new LazyAdditionX(coeff));
    }
    
//     std::cout<<"LazyMultiplicationX::LazyMultiplicationX resultat = "<< *this <<std::endl;
}

double LazyMultiplicationX::compact(std::list<LazyParser*> in)
{
    std::list<LazyParser*> vec;    
    for ( auto iter : in)
    {
        if ( iter->typep_ == LAZYP_MULTIPLICATIONX)
        {
            LazyMultiplicationX* AX = (LazyMultiplicationX*) iter;
            for (auto& iter1 : AX->p_)
                vec.push_back( iter1);
        }else 
        {
            vec.push_back(iter);
        }
    }    
    
    double cst = 1.0;
    p_.clear();
    for ( auto iter : vec)
    {
        if ( iter->typep_ == LAZYP_CONSTANT)
        {
            LazyConstant* c = (LazyConstant*)iter;
            cst *= c->value_;
        }else 
        {
            p_.push_back(iter);
        }
    }
        
    return cst;
//     if ( cst)
//     {
//         p_.push_back( new LazyAdditionX(cst));
//     }else
//     {
//         p_.clear();
//     }
//     p_.sort(compareLazyParser);
}

LazyCreator* LazyMultiplicationX::explose()
{
    if (explosed_ == nullptr)
    {       
        
        int cpt = 0;
        for (auto& iter : p_)   if ( !LMANAGER.is_one(iter))
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
    std::string cmd;
    int cpt = 0;
    for (auto&i : p_)
    {
        if (cpt++)  cmd +="*";
        cmd += i->get_name();
    }
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
    std::cout<<tab<<"LazyMultiplicationX:("<<this<<"): "<<std::endl;
    for (auto iter : p_)
        iter->print(tab+"\t");
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
