#include "LazyMultiplicationX.hpp"
#include "LazyMultiplication.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyMultiplicationX::LazyMultiplicationX(std::list<LazyValue*>& a)
{
    type_ = LAZYMULTIPLICATIONX;
    p_ = a;
    p_.sort();
    compute();
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
    
    double cst = 1.0;
    p_.clear();
    for ( auto iter : vec)
    {
        if ( iter->type_ == LAZYCONSTANT)
        {
            LazyConstant* c = (LazyConstant*)iter;
            cst *= c->value_;
        }else 
        {
            p_.push_back(iter);
        }
    }
        
    if ( cst)
    {
        p_.push_back(LMANAGER.add_constant(cst));
//     p_.push_back(new LazyConstant(cst));
    }   
}



LazyValue* LazyMultiplicationX::explose()
{
    if (!explosed_)
    {
        explosed_ = true;
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
    if (!exploded_ptr_)
    {
        std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" SHOULD NOT HAPPEN"<<std::endl;
        exit(123);
    }
    return exploded_ptr_;
}

std::string LazyMultiplicationX::file_print( const std::string& varname)
{
    std::cerr<<"LazyMultiplicationX::file_print : This should not happen"<<std::endl;
    std::exit(12);
    
    std::string cmd = varname+"["+ std::to_string(id_)+"] = 1 ";
    for (auto iter : p_)
        cmd += "*"+ iter->file_subname(varname) ;
    return   cmd;
}

std::string LazyMultiplicationX::get_string( )
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
    for (auto iter : p_)
    {
        iter->print_equation();
        std::cout<<" * ";   
    }
    std::cout<<1<<")";
}
