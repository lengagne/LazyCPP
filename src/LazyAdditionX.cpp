#include "LazyAdditionX.hpp"
#include "LazyAddition.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyAdditionX::LazyAdditionX(std::list<LazyParser*>& a)
{
//     std::cout<<"LazyAdditionX(std::list<LazyValue*>& a)"<<std::endl;
//     for (auto& i : a)
//         std::cout<<"\ta = (@"<<i<<") : "<< *i <<std::endl;
    
    typep_ = LAZYP_ADDITIONX;    
    for ( auto& i : a)
    {
        switch(i->typep_)
        {
            case(LAZYP_ADDITIONX):
                for (auto& it : ((LazyAdditionX*)i)->p_)
                {
//                     std::cout<<"LAZYP_ADDITIONX : "<< it.first << "!"<< it.second<<std::endl;
                    p_[it.first] += it.second;
                }
                break;
                
            case(LAZYP_MULTIPLICATIONX):
//                 std::cout<<"LAZYP_MULTIPLICATIONX"<<std::endl;
                // extract the constant part
                p_[LMANAGER.add_parser(((LazyMultiplicationX*)i)->get_without_constant())] = ((LazyMultiplicationX*)i)->get_constant();
                break;
            default:
//                 std::cout<<"default"<<std::endl;
                p_[i] += 1.0;
                
        }
    }
    remove_zeros();
//     std::cout<<"Result LazyAdditionX (@"<<this<<") = "<< *this <<std::endl<<std::endl;
}

LazyAdditionX::LazyAdditionX(double value)
{
    typep_ = LAZYP_ADDITIONX;
    if (value)
        p_[ LMANAGER.get_one()] = value;
}

LazyAdditionX::LazyAdditionX(double coeff, LazyParser* in)
{
    typep_ = LAZYP_ADDITIONX;
    switch( in->typep_)
    {
        case(LAZYP_ADDITIONX):
            p_ = ((LazyAdditionX*)in)->p_;
            for(auto& i:p_)
                i.second *= coeff;
            break;
//         case(LAZYP_MULTIPLICATIONX):
//             std::cout<<"LAZYP_MULTIPLICATIONX"<<std::endl;
//             std::cout<<" vec = "<< *LMANAGER.add_parser(((LazyMultiplicationX*)in)->get_without_constant())<<std::endl;
//             std::cout<<" val = "<< ((LazyMultiplicationX*)in)->get_constant() <<std::endl;
//             p_[LMANAGER.add_parser(((LazyMultiplicationX*)in)->get_without_constant())] = ((LazyMultiplicationX*)in)->get_constant()*coeff;
//             break;

        default:
            p_[ in] = coeff;
    }
}
// LazyAdditionX::LazyAdditionX(double coeff, LazyValue* in)
// {
//     type_ = LAZYADDITIONX;
//     explosed_ = false;
//     p_[in] = coeff;
//     remove_zeros();
//     compute();
// }

// inline void LazyAdditionX::compute()
// {
//     value_ = 0;
//     for (auto& iter : p_)
//         value_ += iter.first->value_;
// }    

// void LazyAdditionX::compact()
// {
// //     std::cout<<"debut compact : "<<std::endl;
//     if (compacted_) return;
// 
//     compacted_ = true;
//     
//     std::list<LazyValue*> vec;
//     
//     for ( auto& iter : p_)
//     {
//         iter.first->compact(); 
//         if ( iter.first->type_ == LAZYADDITIONX)
//         {
//             LazyAdditionX* AX = (LazyAdditionX*) iter.first;
//             for (auto& iter1 : AX->p_)
//             {
//                 p_[iter1.first] += iter1.second;
//             }
//         }else 
//         {
// //             p_[iter.first] += iter.second;
// //             vec.push_back(iter);
//         }
//     }    
//    remove_zeros(); 
// //     double cst = 0.0;
// //     p_.clear();
// //     for ( auto iter : vec)
// //     {
// //         if ( iter->type_ == LAZYCONSTANT)
// //         {
// //             LazyConstant* c = (LazyConstant*)iter;
// //             cst += c->value_;
// //         }else 
// //         {
// //             p_.push_back(iter);
// //         }
// //     }
// //         
// //     if ( cst)
// //     {
// // //         p_.push_back(new LazyConstant(cst));
// //         p_.push_back(LMANAGER.add_constant(cst));
// //     }   
// //    std::cout<<"end compact = "<<*this <<std::endl;
// }

LazyCreator* LazyAdditionX::explose()
{
//     std::cout<<"We explose LazyAdditionX("<<this<<") "<< * this <<std::endl;
    if (explosed_ == nullptr)
    {
        int cpt =0;
        for (auto& iter : p_)
        {
//             std::cout<<"We explose LazyAdditionX : ("<< (LMANAGER.is_one(iter.first))<<") "<< *(iter.first)<<"  @" <<iter.second <<std::endl;
            if (cpt++ == 0)
            {
                if (LMANAGER.is_one(iter.first))
                    explosed_ = LMANAGER.add_constant(iter.second);
//                 std::cout<<"\tWe explose LazyAdditionX case 0"<<std::endl;
                else
                    explosed_ = LMANAGER.add_multiplication(LMANAGER.add_constant(iter.second),iter.first->explose());                
                
//                 iter.first->explose();                
            }else
            {
                if (iter.second ==1.0)
                {
//                     std::cout<<"We explose LazyAdditionX case 1"<<std::endl;
                    explosed_ = LMANAGER.add_addition(explosed_,iter.first->explose());
    //                 m = LMANAGER.add_addition(m,iter.first);
                }else if (iter.second ==-1.0)
                {
//                     std::cout<<"We explose LazyAdditionX case 2"<<std::endl;
                    explosed_ = LMANAGER.add_soustraction(explosed_,iter.first->explose());
    //                 m = LMANAGER.add_soustraction(m,iter.first);
                }else
                {
//                     std::cout<<"We explose LazyAdditionX case 3"<<std::endl;
                    LazyCreator* tmp = LMANAGER.add_multiplication(LMANAGER.add_constant(iter.second),iter.first->explose());                
                    explosed_ = LMANAGER.add_addition(explosed_,tmp);
    //                 m = LMANAGER.add_addition(m,tmp);
                }
            }
//     std::cout<<"LazyAdditionX explosed("<<this<<") = "<< *explosed_<<std::endl;            
        }
    }    
//     std::cout<<"LazyAdditionX explosed("<<this<<") = "<< *explosed_<<std::endl;
//     std::cout<<"End of explose()"<<std::endl;
    std::cout<<"equation : "<< explosed_->get_equation()<<std::endl;
    explosed_->print_tree();
    std::cout<<std::endl<<std::endl;
    return explosed_;
}

double LazyAdditionX::get_double()
{
    if (! is_double())
    {
        std::cerr<<"ERROR in "<<__FILE__<<" at line "<< __LINE__<<std::endl;
        exit(44);
    }
    return p_[LMANAGER.get_one()];
}

std::string LazyAdditionX::get_name() const
{
    std::string cmd;
    int cpt = 0;
    for (auto&i : p_)
    {
        if (cpt++)  cmd +="+";
        cmd += std::to_string(i.second);
        if (i.first != LMANAGER.get_one())   cmd +=  "*" + i.first->get_name() ;
    }
    return cmd;
}


bool LazyAdditionX::is_double() const
{
    if (p_.size() != 1){
        return false;
    }
    
    std::map<LazyParser*, double>::const_iterator it = p_.begin();    
    if (it->first == LMANAGER.get_one())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LazyAdditionX::is_zero() const
{
    return (p_.size() ==0);
}


// std::string LazyAdditionX::file_print( const std::string& varname)
// {
// //     std::cerr<<"LazyAdditionX::file_print This should not happen"<<std::endl;
// //    print_equation();std::cout<<std::endl;
// //     print();std::cout<<std::endl;
// //     std::exit(12);    
//     std::string cmd = varname+"["+ std::to_string(id_)+"] =";
//     int cpt=0;
//     for (auto& iter : p_)
//     {
//         if (cpt++)
//             cmd += "+ ";
//         if (iter.second == 1.0)
//             cmd += iter.first->file_subname(varname) ;
//         else
//             cmd += std::to_string(iter.second) + "*" + iter.first->file_subname(varname) ;
//     }
//     return   cmd;
// }

// std::string LazyAdditionX::get_string( )const 
// {
//     std::string cmd = "(";
//     uint cpt = 0;
//     for (auto& iter : p_)
//     {
//         if(cpt++)
//             cmd += "+ ";
//         if (iter.second == 1.0)
//             cmd += iter.first->get_string();
//         else
//             cmd += std::to_string(iter.second)+ "*" + iter.first->get_string();
//     }
//     cmd = cmd +")";
//     return cmd;
// }

void LazyAdditionX::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyAdditionX:("<<this<<"): "<<std::endl;
    int cpt = 0;
    for (auto& iter : p_)
    {
        if (cpt ++)std::cout<<"+";
        std::cout<<iter.second<<"*";
        iter.first->print(tab+"\t");
    }
}   
    
// void LazyAdditionX::print_equation()
// {
//     uint cpt = 0;
//     std::cout<<"LazyAdditionX(";
//     for (auto& iter : p_)
//     {
//         if (cpt++)
//             std::cout<<" + "<< iter.second<<"*";   
//         iter.first->print_equation();
//         
//     }
//     std::cout<<")";
// }

// void LazyAdditionX::propag_update(int v)
// {
//     update_ = v;
//     for (auto iter : p_)
//     {
//         iter.first->propag_update(v);
// //         update_ = update_ || iter->update_;
//     }
// }


void LazyAdditionX::remove_zeros()
{
    // erase the zero values
    for (auto it = p_.begin(); it != p_.end(); ) 
    {
        if (it->second == 0.0 || LMANAGER.is_zero( it->first))
        {
            it = p_.erase(it);
        } else {
            ++it;
        }
    }
}

// void LazyAdditionX::update_list(std::vector<LazyValue*>& vec, int current)
// {
// //     std::cerr<<"FILE : "<< __FILE__<<" line : "<< __LINE__<<std::endl;
// //     std::cerr<<"THIS FONCTION SHOULD NOT BE CALLED"<<std::endl;
// //     std::exit(1234);
//     
//     if (update_ < current)
//     {        
//         update_ = current;
//         for (auto& iter : p_)
//         {
//             iter.first->update_list(vec,current);
//         }
//         vec.push_back(this);  
//     }
//     
// }   
// 
// bool LazyAdditionX::operator == (const LazyAdditionX& A) const
// {
// //     if (p_.size() != A.p_.size())
// //         return false;
//        
//     return p_ == A.p_;
// }
