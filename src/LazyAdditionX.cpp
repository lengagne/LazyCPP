#include "LazyAdditionX.hpp"
#include "LazyAddition.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyAdditionX::LazyAdditionX(std::list<LazyParser*>& a)
{
    std::cout<<"LazyAdditionX(std::list<LazyValue*>& a)"<<std::endl;
    for (auto& i : a)
        std::cout<<"\t Ajout de(@"<<i<<") : "<< *i <<std::endl;    
    typep_ = LAZYP_ADDITIONX;    
    for ( auto& i : a)
    {
        switch(i->typep_)
        {
            case(LAZYP_ADDITIONX):
                for (auto& it : ((LazyAdditionX*)i)->p_)
                {
                    p_[it.first] += it.second;
                }
                break;
                
            case(LAZYP_MULTIPLICATIONX):
                // extract the constant part
                p_[LMANAGER.add_parser(((LazyMultiplicationX*)i)->get_without_constant())] = ((LazyMultiplicationX*)i)->get_constant();
                break;
            default:
                p_[i] += 1.0;
        }
    }
    remove_zeros();
    std::cout<<"LazyAdditionX result = "<<*this <<std::endl;
    print();
    std::cout<<"TREE"<<std::endl;
    explose()->print_tree();
    std::cout<<"*******************"<<std::endl<<std::endl;
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

LazyCreator* LazyAdditionX::explose()
{
    if (explosed_ == nullptr)
    {
        if (p_.size() == 0)
        {
            explosed_ = LMANAGER.get_zero()->explose();
            return explosed_;
        }
        
        int cpt =0;
        for (auto& iter : p_)
        {
            if (cpt++ == 0)
            {
                if (LMANAGER.is_one(iter.first))
                    explosed_ = LMANAGER.add_constant(iter.second);
                else
                    explosed_ = LMANAGER.add_multiplication(LMANAGER.add_constant(iter.second),iter.first->explose());                
            }else
            {
                if (iter.second ==1.0)
                {
                    explosed_ = LMANAGER.add_addition(explosed_,iter.first->explose());
                }else if (iter.second ==-1.0)
                {
                    explosed_ = LMANAGER.add_soustraction(explosed_,iter.first->explose());
                }else
                {
                    LazyCreator* tmp = LMANAGER.add_multiplication(LMANAGER.add_constant(iter.second),iter.first->explose());                
                    explosed_ = LMANAGER.add_addition(explosed_,tmp);
                }
            }
        }
    }    
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
    if (is_zero())
        return "ZERO";
    
    std::string cmd;
    int cpt = 0;
    for (auto&i : p_)
    {
        if (cpt++)  cmd +="+";
        if (i.second != 1.0) cmd += std::to_string(i.second) + "*";
//         if (i.first != LMANAGER.get_one()) 
            cmd +=  i.first->get_name() ;
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

void LazyAdditionX::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyAdditionX:("<<this<<"): "<<std::endl;
    int cpt = 0;
    for (auto& iter : p_)
    {
        if (cpt ++)std::cout<<"+";
        if (iter.second != 1.0) std::cout<<iter.second<<"*";
        iter.first->print(tab+"\t");
    }
}   
    
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
