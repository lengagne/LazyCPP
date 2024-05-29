#include "LazyMultiplicationX.hpp"
#include "LazyMultiplication.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyMultiplicationX::LazyMultiplicationX(std::list<LazyValue*>& a)
{    
    type_ = LAZYMULTIPLICATIONX;
    
    double coeff = 1.0;
    
    for ( auto iter : a)
    {
        if ( iter->type_ == LAZYCONSTANT)
        {
            coeff *= iter->value_;
        }else
        {
            p_.push_back(iter);
        }
    }
    
    if (coeff != 1.0)
        p_.push_back( LMANAGER.add_constant(coeff));
    p_.sort(compareLazyValue);
    compute();
    compact();
}

inline void LazyMultiplicationX::compute()
{
    value_ = 1.0;
    for (auto iter : p_)
        value_ *= iter->value_;
}    

void LazyMultiplicationX::compact()
{
    if (compacted_) return;
    compacted_ = true;
        
    std::list<LazyValue*> vec;    
    for ( auto iter : p_)
    {
        iter->compact(); 
        if ( iter->type_ == LAZYMULTIPLICATIONX)
        {
            LazyMultiplicationX* AX = (LazyMultiplicationX*) iter;
            for (auto& iter1 : AX->p_)
                vec.push_back( iter1);
        }else 
        {
            vec.push_back(iter);
        }
    }    
    p_.sort(compareLazyValue);
}



LazyValue* LazyMultiplicationX::explose()
{
//     std::cout<<"deb : LazyMultiplicationX::explose()"<<std::endl;
    p_.sort(compareLazyValue);
    if (!explosed_)
    {        
        explosed_ = true;
        if (p_.size() == 1)
        {
            exploded_ptr_ = p_.front();
            return exploded_ptr_;
        }else
        {
            LazyValue* m;
            uint cpt=0;
            for (auto iter : p_)
            {
                if (cpt++ ==0)
                {
                    m = iter->explose();
                }else
                {
                    m = LMANAGER.add_multiplication(m,iter->explose());
    //                 m = new LazyMultiplication(m,iter->explose());
                }
            }        
            exploded_ptr_ = m;
        }
    }
    if (!exploded_ptr_)
    {
        std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" SHOULD NOT HAPPEN"<<std::endl;
        exit(123);
    }
//     std::cout<<"fin : LazyMultiplicationX::explose()"<<std::endl;
    return exploded_ptr_;
}

std::string LazyMultiplicationX::file_print( const std::string& varname)
{
//     std::cerr<<"LazyMultiplicationX::file_print : This should not happen"<<std::endl;
//     std::exit(12);
    
    std::string cmd = varname+"["+ std::to_string(id_)+"] = ";
    uint cpt = 0;
    for (auto iter : p_)
    {
        if (cpt++)
            cmd +="*";
        cmd +=  iter->file_subname(varname) ;
    }
    return   cmd;
}

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

void LazyMultiplicationX::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyMultiplicationX:("<<this<<"): MultiplicationX ("<<value_<<")"<<std::endl;
    for (auto iter : p_)
        iter->print(tab+"\t",index);
}   
    
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
}
