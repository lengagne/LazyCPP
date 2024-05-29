#include "LazyAdditionX.hpp"
#include "LazyAddition.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyAdditionX::LazyAdditionX(std::list<LazyValue*>& a)
{
//     std::cout<<"\n\nLazyAdditionX(std::list<LazyValue*>& a)"<<std::endl;
//     for (auto& i : a)
//         std::cout<<"LazyAdditionX : "<< *i <<std::endl;
    
    type_ = LAZYADDITIONX;
    
    for ( auto& i : a)
    {
        // extract constant from variable
        double coeff;
        LazyMultiplication* I;
        LazyMultiplicationX* XI;
        LazyValue*Xout;
        std::list<LazyValue*> a;
        bool test;
        switch(i->type_)
        {
            case(LAZYMULTIPLICATION): 
                I = (LazyMultiplication*) i;
                if (I->a_->type_ == LAZYCONSTANT && I->b_->type_ != LAZYCONSTANT)
                {
//                     std::cout<<"CASE 1"<<std::endl;
                    p_[I->b_] += I->a_->value_;
                }else if (I->b_->type_ == LAZYCONSTANT && I->a_->type_ != LAZYCONSTANT)
                {
//                     std::cout<<"CASE 2"<<std::endl;
                    p_[I->a_] += I->b_->value_;
                }else if (I->a_->type_ != LAZYCONSTANT && I->b_->type_ != LAZYCONSTANT)
                {
//                     std::cout<<"CASE 3"<<std::endl;
                    p_[i] += 1.0;
                }else
                {
                    std::cout<<"This case must not happen"<<std::endl;
                }
                break;
                
           case(LAZYMULTIPLICATIONX): 
                coeff = 1.0;
                XI = (LazyMultiplicationX*) i;
//                 std::cout<<"ajout de LAZYMULTIPLICATIONX : "<<*i<<std::endl;
                test = false;
                a.clear();
//                 for (auto& iter : XI->p_)
                for (auto it = XI->p_.begin(); it != XI->p_.end(); ) 
                {
                    if((*it)->type_ == LAZYCONSTANT)
                    {
                        test = true;
                        coeff *= (*it)->value_;
//                         std::cout<<"mutliplication par "<< (*it)->value_ <<std::endl;
//                         it = XI->p_.erase(it);
                    }else
                    {
//                         std::cout<<"on garde "<< *(*it) <<std::endl;
                        a.push_back(*it);
                    }
                    ++it;
                }
                
//                 if (test)
//                 {                    
                    Xout = LMANAGER.add_multiplicationX(a);
                    p_[Xout] += coeff;
//                     std::cout<<"on ajoute "<< coeff<< " *"<< *Xout <<std::endl;
//                     std::cout<<"on obtient : "<< p_[Xout]<<std::endl;
//                 }else
//                 {                    
//                     p_[i] += 1.0;
// //                     std::cout<<"pas de Lazyconstant : "<<i<<std::endl;
//                 }
                break;              
                
            case(LAZYCONSTANT):
//                 std::cout<<"on ajoute une constante : "<< i->value_ <<std::endl;
                p_[ LMANAGER.get_one()] += i->value_;
                break;
            default:
                p_[i] += 1.0;
//                 std::cout<<"Must plan this case "<<std::endl;
                break;
        }
    }
//     p_ = a;

    remove_zeros();
    
//     p_.sort(compareLazyValue);
    compute();
//     std::cout<<"LazyAdditionX = "<< *this <<std::endl<<std::endl;
}

inline void LazyAdditionX::compute()
{
    value_ = 0;
    for (auto& iter : p_)
        value_ += iter.first->value_;
}    

void LazyAdditionX::compact()
{
//     std::cout<<"debut compact : "<<std::endl;
    if (compacted_) return;

    compacted_ = true;
    
    std::list<LazyValue*> vec;
    
    for ( auto& iter : p_)
    {
        iter.first->compact(); 
        if ( iter.first->type_ == LAZYADDITIONX)
        {
            LazyAdditionX* AX = (LazyAdditionX*) iter.first;
            for (auto& iter1 : AX->p_)
            {
                p_[iter1.first] += iter1.second;
            }
        }else 
        {
//             p_[iter.first] += iter.second;
//             vec.push_back(iter);
        }
    }    
   remove_zeros(); 
//     double cst = 0.0;
//     p_.clear();
//     for ( auto iter : vec)
//     {
//         if ( iter->type_ == LAZYCONSTANT)
//         {
//             LazyConstant* c = (LazyConstant*)iter;
//             cst += c->value_;
//         }else 
//         {
//             p_.push_back(iter);
//         }
//     }
//         
//     if ( cst)
//     {
// //         p_.push_back(new LazyConstant(cst));
//         p_.push_back(LMANAGER.add_constant(cst));
//     }   
//    std::cout<<"end compact = "<<*this <<std::endl;
}

LazyValue* LazyAdditionX::explose()
{
//     std::cout<<"deb : LazyAdditionX::explose()"<<std::endl;
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
    if (!explosed_)
    {        
        explosed_ = true;
        LazyValue* m = LMANAGER.get_zero();
        for (auto& iter : p_)
        {
            if (iter.second !=1.0)
            {
                LazyValue* tmp = LMANAGER.add_multiplication(LMANAGER.add_constant(iter.second),iter.first);                
                m = LMANAGER.add_addition(m,tmp->explose());
//                 m = LMANAGER.add_addition(m,tmp);
            }else
            {
                m = LMANAGER.add_addition(m,iter.first->explose());
//                 m = LMANAGER.add_addition(m,iter.first);
            }
        }
        exploded_ptr_ = m;
//         std::cout<<"after explose : "<< *m <<std::endl;
/*        if (p_.size() == 2)
        {
            LazyValue* m;
            uint cpt=0;
            for (auto& iter : p_)
            {
                if (cpt++ ==0)
                {
                    m = iter.first->explose();
                }else
                {
                    m = LMANAGER.add_addition(m,iter.first->explose());                
                }
            }    
            exploded_ptr_ = m;
        }else
        {
        
            std::list<LazyValue*> tmp;            
            for (auto& iter : p_)
            {
                LazyValue* m = iter.first->explose(); 
                tmp.push_back(m);
            }        
            exploded_ptr_ = new LazyAdditionX(tmp);
        }    */    
    }    
    if (!exploded_ptr_)
    {
        std::cerr<<"ERROR in "<< __FILE__<<" at line "<<__LINE__<<" SHOULD NOT HAPPEN"<<std::endl;
        exit(123);
    }
//     std::cout<<"fin : LazyAdditionX::explose()"<<std::endl;
    return exploded_ptr_;
}


std::string LazyAdditionX::file_print( const std::string& varname)
{
    std::cerr<<"LazyAdditionX::file_print This should not happen"<<std::endl;
   print_equation();std::cout<<std::endl;
    print();std::cout<<std::endl;
    std::exit(12);    
    std::string cmd = varname+"["+ std::to_string(id_)+"] =";
    for (auto& iter : p_)
    {
        if (iter.second == 1.0)
            cmd += "+ " + iter.first->file_subname(varname) ;
        else
            cmd += "+ " +std::to_string(iter.second) + "*" + iter.first->file_subname(varname) ;
    }
    return   cmd;
}

std::string LazyAdditionX::get_string( )const 
{
    std::string cmd = "(";
    uint cpt = 0;
    for (auto& iter : p_)
    {
        if (iter.second == 1.0)
            cmd += "+ " + iter.first->get_string();
        else
            cmd = cmd+"+"+ std::to_string(iter.second)+ "*" + iter.first->get_string();
    }
    cmd = cmd +")";
    return cmd;
}

void LazyAdditionX::print( const std::string& tab,uint index) 
{
    std::cout<<tab<<"LazyAdditionX:("<<this<<"): AdditionX ("<<value_<<")"<<std::endl;
    for (auto& iter : p_)
    {
        std::cout<<iter.second<<"*";
        iter.first->print(tab+"\t",index);
    }
}   
    
void LazyAdditionX::print_equation()
{
    uint cpt = 0;
    std::cout<<"LazyAdditionX(";
    for (auto& iter : p_)
    {
        if (cpt++)
            std::cout<<" + "<< iter.second<<"*";   
        iter.first->print_equation();
        
    }
    std::cout<<")";
}

void LazyAdditionX::propag_update(int v)
{
    update_ = v;
    for (auto iter : p_)
    {
        iter.first->propag_update(v);
//         update_ = update_ || iter->update_;
    }
}


void LazyAdditionX::remove_zeros()
{
    // erase the zero values
    for (auto it = p_.begin(); it != p_.end(); ) 
    {
        if (it->first == LMANAGER.get_zero() ||  it->second == 0.0) {
            it = p_.erase(it);
        } else {
            ++it;
        }
    }
}

void LazyAdditionX::update_list(std::vector<LazyValue*>& vec, int current)
{
//     std::cerr<<"FILE : "<< __FILE__<<" line : "<< __LINE__<<std::endl;
//     std::cerr<<"THIS FONCTION SHOULD NOT BE CALLED"<<std::endl;
//     std::exit(1234);
    
    if (update_ < current)
    {        
        update_ = current;
        for (auto& iter : p_)
        {
            iter.first->update_list(vec,current);
        }
        vec.push_back(this);  
    }
    
}   

bool LazyAdditionX::operator == (const LazyAdditionX& A) const
{
//     if (p_.size() != A.p_.size())
//         return false;
       
    return p_ == A.p_;
}
