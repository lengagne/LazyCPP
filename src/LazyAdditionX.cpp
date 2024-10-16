#include "LazyAdditionX.hpp"
#include "LazyAddition.hpp"
#include "LazyConstant.hpp"
#include "LazyCPP.hpp"

LazyAdditionX::LazyAdditionX( )
{
    typep_ = LAZYP_ADDITIONX;
}


LazyAdditionX::LazyAdditionX(std::list<LazyParser*>& a)
{
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
                
//             case(LAZYP_MULTIPLICATIONX):
//                 // extract the constant part
//                 p_[LMANAGER.add_parser(((LazyMultiplicationX*)i)->get_without_constant())] = ((LazyMultiplicationX*)i)->get_constant();
//                 break;
            default:
                p_[i] += 1.0;
        }
    }
    remove_zeros();
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

LazyParser* LazyAdditionX::do_simplification()
{
    LazyAdditionX* out = new LazyAdditionX();
    double constant = 0.0;
    for (auto& iter : p_)
    {
        LazyParser* s = iter.first->simplify();
        switch (s->typep_)
        {
            case(LAZYP_CONSTANT):
                constant += ((LazyConstant*) s)->value_ * iter.second;
                break;
            
            case(LAZYP_ADDITIONX):
                for (auto& i : ((LazyAdditionX*) s)->p_)
                {
                    out->p_[i.first] += i.second;
                }
                break;                
                
            case(LAZYP_INPUT):
            case(LAZYP_MULTIPLICATIONX):
            case(LAZYP_COSINUS):
            case(LAZYP_SINUS):                    
                out->p_[s] += iter.second;
                break;
                
            default:
                std::cerr<<"In file "<< __FILE__<<" at line "<< __LINE__ <<" the type "<< s->typep_ <<" is not implemented yet."<<std::endl;
                out->p_[s] += iter.second;
        }
        
    }
//     std::cout<<"constant = "<< constant <<std::endl;
    if (constant != 0)
    {
//         out->p_[LMANAGER.add_constant_parser(constant)] += 1.0;
        out->p_[LMANAGER.get_one()] += constant;
    }
    
    out->remove_zeros();
    
    if( out->p_.size() == 0.0)
        return LMANAGER.get_zero();
    return out;
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
                {
                    explosed_ = LMANAGER.add_constant(iter.second);
                }
                else
                {
                    if (iter.second == 1.0)
                        explosed_ = iter.first->explose();
                    else                    
                        explosed_ = LMANAGER.add_multiplication(LMANAGER.add_constant(iter.second),iter.first->explose());                
                }
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
    
    std::string cmd = "[";
    int cpt = 0;
    for (auto&i : p_)
    {
        if (cpt++)  cmd +="+";
        if (i.second != 1.0) cmd += std::to_string(i.second) + "*";
//         if (i.first != LMANAGER.get_one()) 
            cmd +=  i.first->get_name() ;
    }
    cmd+="]";
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
//     std::cout<<"is zero for : "<< *this <<std::endl;
    
    if(p_.size() == 0)
        return true;
    
    if (p_.size() == 1){
        std::map<LazyParser*, double>::const_iterator it = p_.begin();  
        if (it->second == 0.0)
            return true;
        if (LMANAGER.is_zero(it->first))
            return true;        
    }
//     std::cout<<"return FALSE"<<std::endl;
    return false;
}

void LazyAdditionX::print( const std::string& tab) const
{
    std::cout<<tab<<"LazyAdditionX:("<<get_name()<<"): "<<std::endl;
    std::cout<<tab<<"["<<std::endl;
    int cpt = 0;
    for (auto& iter : p_)
    {
        if (cpt ++)std::cout<<"+";
        if (iter.second != 1.0) std::cout<<iter.second<<"*";
        iter.first->print(tab+"\t");
    }
    std::cout<<tab<<"]"<<std::endl;
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

bool LazyAdditionX::operator < ( const LazyAdditionX& in) const
{
    if ( p_.size() < in.p_.size())  return true;
    if ( p_.size() > in.p_.size())  return false;
    
    auto it = p_.begin();
    auto it2 = in.p_.begin();
    for (; it != p_.end() && it2 != in.p_.end(); ) 
    {
        if( it->second < it2->second)   return true;
        if( it->second > it2->second)   return false;
        if( it->first < it2->first)   return true;
        if( it->first > it2->first)   return false;
        
        ++it;
        ++it2;
    }
    return false;
}
