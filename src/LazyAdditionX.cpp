#include "LazyAdditionX.hpp"
#include "LazyAddition.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyAdditionX::LazyAdditionX(std::list<LazyValue*>& a)
{
    type_ = LAZYADDITIONX;
    p_ = a;
    p_.sort();
    compute();
}

inline void LazyAdditionX::compute()
{
    value_ = 0;
    for (auto iter : p_)
        value_ += iter->value_;
}    

void LazyAdditionX::compact()
{
    if (compacted_) return;

    compacted_ = true;
    
    std::list<LazyValue*> vec;
    
    for ( auto iter : p_)
    {
        iter->compact(); 
        if ( iter->type_ == LAZYADDITIONX)
        {
            LazyAdditionX* AX = (LazyAdditionX*) iter;
            for (auto& iter1 : AX->p_)
                vec.push_back( iter1);
        }else 
        {
            vec.push_back(iter);
        }
    }    
    
    double cst = 0.0;
    p_.clear();
    for ( auto iter : vec)
    {
        if ( iter->type_ == LAZYCONSTANT)
        {
            LazyConstant* c = (LazyConstant*)iter;
            cst += c->value_;
        }else 
        {
            p_.push_back(iter);
        }
    }
        
    if ( cst)
    {
//         p_.push_back(new LazyConstant(cst));
        p_.push_back(LMANAGER.add_constant(cst));
    }   
}

LazyValue* LazyAdditionX::explose()
{
//     if (!explosed_)
//     {
//         explosed_ = true;
//         LazyValue* m;
//         uint cpt=0;
//         for (auto iter : p_)
//         {
//             if (cpt++ ==0)
//             {
//                 m = iter->explose();
//             }else
//             {
//                 m = LMANAGER.add_addition(m,iter->explose());                
// //                 m = new LazyAddition(m,iter->explose());
//             }
//         }        
//         exploded_ptr_ = m;
//     }
    p_.sort();
    if (!explosed_)
    {
        
        explosed_ = true;
        if (p_.size() == 2)
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
                    m = LMANAGER.add_addition(m,iter->explose());                
                }
            }    
            exploded_ptr_ = m;
        }else
        {
        
            std::list<LazyValue*> tmp;            
            for (auto iter : p_)
            {
                LazyValue* m = iter->explose(); 
                tmp.push_back(m);
            }        
            exploded_ptr_ = new LazyAdditionX(tmp);
        }
        
    }    
    
    if (!exploded_ptr_)
    {
        std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" SHOULD NOT HAPPEN"<<std::endl;
        exit(123);
    }
    return exploded_ptr_;
}


std::string LazyAdditionX::file_print( const std::string& varname)
{
//     std::cerr<<"LazyAdditionX::file_print This should not happen"<<std::endl;
/*    print_equation();std::cout<<std::endl;
    print();std::cout<<std::endl;
    std::exit(12);   */ 
    std::string cmd = varname+"["+ std::to_string(id_)+"] =";
    for (auto iter : p_)
        cmd += "+ " + iter->file_subname(varname) ;
    cmd +=  " /* " + get_string() + "*/";
    return   cmd;
}

std::string LazyAdditionX::get_string( )
{
    std::string cmd = "(";
    uint cpt = 0;
    for (auto iter : p_)
    {
        if (cpt++)  cmd = cmd +"+";
        cmd = cmd+ iter->get_string();
    }
    cmd = cmd +")";
    return cmd;
}

void LazyAdditionX::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyAdditionX:("<<this<<"): AdditionX ("<<value_<<")"<<std::endl;
    for (auto iter : p_)
        iter->print(tab+"\t",index);
}   
    
void LazyAdditionX::print_equation()
{
    uint cpt = 0;
    std::cout<<"LazyAdditionX(";
    for (auto iter : p_)
    {
        if (cpt++)
            std::cout<<" + ";   
        iter->print_equation();
        
    }
    std::cout<<")";
}

void LazyAdditionX::update_list(std::vector<LazyValue*>& vec, int current)
{
//     std::cerr<<"FILE : "<< __FILE__<<" line : "<< __LINE__<<std::endl;
//     std::cerr<<"THIS FONCTION SHOULD NOT BE CALLED"<<std::endl;
//     std::exit(1234);
    
    if (update_ < current)
    {        
        update_ = current;
        for (auto iter : p_)
        {
            iter->update_list(vec,current);
        }
        vec.push_back(this);  
    }
    
}   
