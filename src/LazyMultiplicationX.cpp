#include "LazyMultiplicationX.hpp"
#include "LazyMultiplication.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyMultiplicationX::LazyMultiplicationX(std::list<LazyParser*>& a)
{    
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
                    coeff *= addx->get_double();
                }else
                {
                    p_.push_back(i);
                }
                break;
            case(LAZYP_MULTIPLICATIONX):                
                mulx = (LazyMultiplicationX*)i;
                for (auto &it : mulx->p_)
                    p_.push_back(it);
                break;
                
            default:
                p_.push_back(i);
        }            
    }
    if (coeff != 1.0)
    {
        p_.push_back( new LazyAdditionX(coeff));
    }
}


LazyCreator* LazyMultiplicationX::explose()
{
    if (explosed_ == nullptr)
    {        
        int cpt = 0;
        for (auto& iter : p_)
        {
            if (cpt == 0)
            {
                explosed_ = iter->explose();
            }else
            {
                explosed_ = LMANAGER.add_multiplication(explosed_,iter->explose());
            }
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

LazyMultiplicationX* LazyMultiplicationX::get_without_constant() const
{
    std::list<LazyParser*> vec;
    for (auto& iter : p_)
    {
        if (iter->typep_ != LAZYP_ADDITIONX || ! ((LazyAdditionX*)iter)->is_double())
        {
            vec.push_back(iter);
        }
    }
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
    std::cout<<tab<<"LazyMultiplicationX:("<<this<<"): MultiplicationX "<<std::endl;
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
